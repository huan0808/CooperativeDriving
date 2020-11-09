#include "gps_read.hpp"
#include <iostream>
// C library headers
#include <stdio.h>
#include <string.h>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <string>
#include <cstdlib>

#include <signal.h>

#include <vector>
#include <ros/ros.h>
#include "localization/gps.h"


//void signal_callback_handler(int signum);

bool GpsReader::InitSerial(){
    using namespace std;
    serial_port = open("/dev/ttyACM0", O_RDWR);
    if(serial_port == -1){
        cout << "open serial failure" << endl;
        return false;
    }
    termios tty;

    // get serial port setting default
    if(tcgetattr(serial_port, &tty) != 0) {
        cout << "tcgetattr error" << endl;
        return false;
    }
    //disable some check mechanism
    tty.c_cflag &= ~PARENB;  
    tty.c_cflag &= ~CSTOPB; 

    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
    tty.c_cflag |= CS8; // 8 bits per byte 
    tty.c_cflag &= ~CRTSCTS; 
    tty.c_cflag |= CREAD | CLOCAL; 
    //disable all special char handle we need raw data
    tty.c_lflag &= ~ICANON; 
    tty.c_lflag &= ~ECHO; 
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL; 
    tty.c_lflag &= ~ISIG; 
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); 

    tty.c_oflag &= ~OPOST; 
    tty.c_oflag &= ~ONLCR; 

    tty.c_cc[VTIME] = 1;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;


    // Set in/out baud rate 
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    
    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 0;
    }

    return true; // success
}

//TODO:
//how to make sure we don't miss frames

bool GpsReader::StartReadGps(){
    using namespace std;

    if(InitSerial() == false){
        return false; 
    }
    else{
        cout <<  "serial init success" << endl;
    }
    //serial_port = gps_read.serial_port;

    cout << "this thread number is " << this_thread::get_id()<< endl;
    char buffer[1024];
    //TODO:
    //how to handle exception to close the serial  
    //signal(SIGINT, signal_callback_handler);

    memset(buffer,0, sizeof(buffer));

    while(ros::ok()){
        const auto start_t = chrono::system_clock::now();
        int n = read(serial_port, &buffer, sizeof(buffer));

        if ( n < 0) {
            perror("read serial");
            return false;
        }

        GPS_STR.assign(buffer);
        auto begin = GPS_STR.find('$');
        auto end = GPS_STR.find('\n');
        int flagGP = 0;
        int flagGT = 0;

        while((flagGP == 0 || flagGT == 0) && begin != -1 && end != -1){
            string FrameData = GPS_STR.substr(begin , end - begin);
            string temp;
            vector<string> INFO;
            for(auto c : FrameData){
                if(c == ','){
                    INFO.push_back(temp);
                    temp.clear();
                    continue;
                }
                temp += c;
            }
            rw_mutex.lock();

            if(GPS_STR[begin+2] == 'P'){
                flagGP = 1;
                int n = 0;
                gps_report.FPD_Header = INFO[n++];
                gps_report.FPD_GPSWeek = INFO[n++];
                gps_report.FPD_GPSTime = INFO[n++];
                gps_report.Heading = INFO[n++];
                gps_report.Pitch = INFO[n++];
                gps_report.Roll = INFO[n++];
                gps_report.Lattitude = INFO[n++];
                gps_report.Longitude = INFO[n++];
                gps_report.Altitude = INFO[n++];
                gps_report.Ve = INFO[n++];
                gps_report.Vn = INFO[n++];
                gps_report.Vu = INFO[n++];
                gps_report.Baseline = INFO[n++];
                gps_report.NSV1 = INFO[n++];
                gps_report.NSV2 = INFO[n++];
                gps_report.Status = INFO[n][1];
                //TODO
                //FPD_CS
                //gps_report.Status = INFO[n][1];
                //FPR_CRLF
                //gps_report.Status = INFO[n][1];
            }
            else{
                flagGT = 1;
                int n = 0;
                imu_report.IMU_Header = INFO[n++]; 
                imu_report.IMU_GPSWeek = INFO[n++]; 
                imu_report.IMU_GPSTime = INFO[n++]; 
                imu_report.GyroX = INFO[n++]; 
                imu_report.GyroY = INFO[n++]; 
                imu_report.GyroZ = INFO[n++]; 
                imu_report.AccX = INFO[n++]; 
                imu_report.AccY = INFO[n++]; 
                imu_report.AccZ = INFO[n++]; 
                imu_report.Tpr = INFO[n++]; 
                //TODO
                /*
                imu_report.IMU_Cs
                imu_report.IMU_CrLf
                */
            }
            rw_mutex.unlock();
            GPS_STR.erase(begin, end - begin + 1);
            auto begin = GPS_STR.find('$');
            auto end = GPS_STR.find('\n');
        }

        const auto end_t = chrono::system_clock::now();
        const auto elapsed_t = chrono::duration<double>(end_t - start_t);
        if (elapsed_t.count() < SERIAL_T) {
            const auto remaining_t = chrono::duration<double>(SERIAL_T) - elapsed_t;
        // cout << "Canbus thread sleeps for " << remaining_t.count() << " seconds." << endl;
            std::this_thread::sleep_for(remaining_t);
        } else {
            cout << "Warning: serial loop spent " << elapsed_t.count() << " seconds larger than " 
                    << SERIAL_T << " seconds. " << endl;
        }
    }
    if(CloseSerial() == false){
        cout << "serial close error" << endl;
        return false;
    }
    return true;
}

/*
void signal_callback_handler(int signum) {
   std::cout << "Caught signal " << signum << std::endl;
   close(serial_port);
   // Terminate program
   exit(signum);
}
*/

bool GpsReader::CloseSerial(){
    if(close(serial_port) == -1){
        std::cout << "close error" << std::endl;
        return false;
    }
    return true;
}

void GpsReader::PublishToRos(){
    ros::Publisher pub_to_GPSINFO = n.advertise<localization::gps>("INFO",1000);
    while(ros::ok()){
        //lock
        rw_mutex.lock();
        localization::gps msg;
        
        //gps info
        msg.FPD_Header = gps_report.FPD_Header;
        msg.FPD_GPSWeek = gps_report.FPD_GPSWeek;
        msg.FPD_GPSTime = gps_report.FPD_GPSTime;
        msg.Heading = gps_report.Heading;
        msg.Pitch = gps_report.Pitch;
        msg.Roll = gps_report.Roll;
        msg.Lattitude = gps_report.Lattitude;
        msg.Longitude = gps_report.Longitude;
        msg.Altitude = gps_report.Altitude;
        msg.Ve = gps_report.Ve;
        msg.Vn = gps_report.Vn;
        msg.Vu = gps_report.Vu;
        msg.Baseline = gps_report.Baseline;
        msg.NSV1 = gps_report.NSV1;
        msg.NSV2 = gps_report.NSV2;
        msg.Status = gps_report.Status;
        msg.FPD_Cs = gps_report.FPD_Cs;
        msg.FPD_CrLf = gps_report.FPD_CrLf;
        
        //imu info
        msg.IMU_Header = imu_report.IMU_Header;
        msg.IMU_GPSWeek = imu_report.IMU_GPSWeek;
        msg.IMU_GPSTime = imu_report.IMU_GPSTime;
        msg.GyroX = imu_report.GyroX;
        msg.GyroY = imu_report.GyroY;
        msg.GyroZ = imu_report.GyroZ;
        msg.AccX = imu_report.AccX;
        msg.AccY = imu_report.AccY;
        msg.AccZ = imu_report.AccZ;
        msg.Tpr = imu_report.Tpr;
        msg.IMU_Cs = imu_report.IMU_Cs;
        msg.IMU_CrLf = imu_report.IMU_CrLf;

        pub_to_GPSINFO.publish(msg);

        //unlock
        rw_mutex.unlock();
        loop_rate.sleep();
        
    }
}



//TODO:
//check this if right
/*
int GpsReader::FPD_Data_Check(char a[],int length)//GPS数据校验
{
    using namespace std;
    int head_n=6;
    string head_str; //帧头
    string CS_str; //数据帧校验位
    int flag=1; //数据标志位
    int CS_dex; 
    unsigned char CS=0;
    int chang=0;
    for(int i=0; i<length-2;i++)
    {
        if(i<head_n)
        {
            head_str += a[i];
        }
        if(flag==3)
        {
            CS_str+=a[i];//在一帧数据中本来存在的校验位
        }
        if(a[i]=='*')
        {
            flag=3;
        }
        if(flag==2)
        {
            CS^=a[i];//异或出来的校验位
            chang++;
        }
        if(a[i]=='$')
        {
            flag=2;
        }
    }
    CS_dex=CS;  //十进制ASCLL码
    if((head_str=="$GPFPD")&&(GPS_Data_Check(CS_str,CS_dex)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/*
int GpsReader::GPS_Data_Check(string hex_n,int dex)
{
    string dex_con_hex;
    string temp;
    int j=0;
    if(dex<=15)
    {
        string temp="";
        if(dex<10)
        {
            temp+=dex+'0';
        }
        else
        {
            temp+=dex-10+'A';
        }
        dex_con_hex=temp;
        for(int i=temp.length()-1;i>=0;i--)
        {
            dex_con_hex[j]=temp[i];
            j++;
        }
    }
    else
    {
        string temp="";
        do
        {
            int dex_tmp=dex%16;
            if(dex_tmp<10)
            {
                temp+=dex_tmp+'0';
            }
            else
            {
                temp+=dex_tmp-10+'A';
            }
            dex/=16;
        }while(dex>=16);
        if(dex<10)
        {
            temp+=dex+'0';
        }
        else
        {
            temp+=dex-10+'A';
        }
        dex_con_hex=temp;
        for(int i=temp.length()-1;i>=0;i--)
        {
            dex_con_hex[j]=temp[i];
            j++;
        }
    }
    if(dex_con_hex.compare(hex_n))//如果两个字符串相等则为0
    {
        return 0;
    }
    else
    {
        return 1;
        
    }
}

*/
