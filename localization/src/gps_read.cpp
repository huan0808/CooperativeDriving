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

    string GPS_STR_;
    int flagGP = 0;
    int flagGT = 0;
    while(ros::ok()){
        const auto start_t = chrono::system_clock::now();
        char buffer[1024];
        memset(buffer,0, sizeof(buffer));
        int n;
        if((n = read(serial_port, &buffer, sizeof(buffer)) )> 0){
            GPS_STR_.assign(buffer);
            auto begin = find(GPS_STR_.begin(),GPS_STR_.end(),'$');
            auto end = find(begin,GPS_STR_.end(),'\n');
            while((flagGP == 0 || flagGT == 0) && begin != GPS_STR_.end() && end != GPS_STR_.end()){
                string FrameData(begin,end);
                if(CheckSum(FrameData)){
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
                    INFO.push_back(temp);
                    rw_mutex_.lock();

                    if(*(begin+2) == 'P'){
                        flagGP = 1;
                        int n = 0;
                        gps_report_.FPD_Header = INFO[n++];
                        gps_report_.FPD_GPSWeek = INFO[n++];
                        gps_report_.FPD_GPSTime = INFO[n++];
                        gps_report_.Heading = INFO[n++];
                        gps_report_.Pitch = INFO[n++];
                        gps_report_.Roll = INFO[n++];
                        gps_report_.Lattitude = INFO[n++];
                        gps_report_.Longitude = INFO[n++];
                        gps_report_.Altitude = INFO[n++];
                        gps_report_.Ve = INFO[n++];
                        gps_report_.Vn = INFO[n++];
                        gps_report_.Vu = INFO[n++];
                        gps_report_.Baseline = INFO[n++];
                        gps_report_.NSV1 = INFO[n++];
                        gps_report_.NSV2 = INFO[n++];
                        gps_report_.Status = INFO[n][1];
                        gps_report_.FPD_Cs += INFO[n][3] ;
                        gps_report_.FPD_Cs += INFO[n][4] ;

                    }
                    else if(*(begin + 2) == 'T'){
                        flagGT = 1;
                        int n = 0;
                        imu_report_.IMU_Header = INFO[n++]; 
                        imu_report_.IMU_GPSWeek = INFO[n++]; 
                        imu_report_.IMU_GPSTime = INFO[n++]; 
                        imu_report_.GyroX = INFO[n++]; 
                        imu_report_.GyroY = INFO[n++]; 
                        imu_report_.GyroZ = INFO[n++]; 
                        imu_report_.AccX = INFO[n++]; 
                        imu_report_.AccY = INFO[n++]; 
                        imu_report_.AccZ = INFO[n++]; 
                        imu_report_.Tpr = INFO[n].substr(0,4); 
                        imu_report_.IMU_Cs += INFO[n][5];
                        imu_report_.IMU_Cs += INFO[n][6];

                    }
                    rw_mutex_.unlock();
                }
                GPS_STR_.erase(GPS_STR_.begin(),end + 1);
                begin = find(GPS_STR_.begin(),GPS_STR_.end(),'$');
                end = find(begin,GPS_STR_.end(),'\n');
            }
            flagGP = 0;
            flagGT = 0;
        }
        else if ( n < 0) {
            perror("read serial");
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
    ros::Publisher pub_to_GPSINFO = n_.advertise<localization::gps>("GPS_INFO",1000);
    while(ros::ok()){
        //lock
        rw_mutex_.lock();
        localization::gps msg;
        
        //gps info
        msg.FPD_Header = gps_report_.FPD_Header;
        msg.FPD_GPSWeek = gps_report_.FPD_GPSWeek;
        msg.FPD_GPSTime = gps_report_.FPD_GPSTime;
        msg.Heading = gps_report_.Heading;
        msg.Pitch = gps_report_.Pitch;
        msg.Roll = gps_report_.Roll;
        msg.Lattitude = gps_report_.Lattitude;
        msg.Longitude = gps_report_.Longitude;
        msg.Altitude = gps_report_.Altitude;
        msg.Ve = gps_report_.Ve;
        msg.Vn = gps_report_.Vn;
        msg.Vu = gps_report_.Vu;
        msg.Baseline = gps_report_.Baseline;
        msg.NSV1 = gps_report_.NSV1;
        msg.NSV2 = gps_report_.NSV2;
        msg.Status = gps_report_.Status;
        msg.FPD_Cs = gps_report_.FPD_Cs;
        
        //imu info
        msg.IMU_Header = imu_report_.IMU_Header;
        msg.IMU_GPSWeek = imu_report_.IMU_GPSWeek;
        msg.IMU_GPSTime = imu_report_.IMU_GPSTime;
        msg.GyroX = imu_report_.GyroX;
        msg.GyroY = imu_report_.GyroY;
        msg.GyroZ = imu_report_.GyroZ;
        msg.AccX = imu_report_.AccX;
        msg.AccY = imu_report_.AccY;
        msg.AccZ = imu_report_.AccZ;
        msg.Tpr = imu_report_.Tpr;
        msg.IMU_Cs = imu_report_.IMU_Cs;


        pub_to_GPSINFO.publish(msg);

        //unlock
        rw_mutex_.unlock();
        loop_rate_.sleep();
        
    }
}

bool GpsReader::CheckSum(const std::string& frame){
    using namespace std;
    if(frame.empty()) return false;
    bool flag = 0;
    unsigned char check1 = frame[1];
    string check2 ;
    for(int i = 2; i < frame.size(); ++i){
        if(frame[i] == '*'){
            flag = true;
        }
        if(flag){
            check2 += frame[i + 1];
            check2 += frame[i + 2];
            break;
        }
        else{
            check1 ^= frame[i];
        }
    }
    return GPS_Data_Check(check2,check1);
}
int GpsReader::GPS_Data_Check(std::string& hex_n,int dex)
{
    using namespace std;
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
