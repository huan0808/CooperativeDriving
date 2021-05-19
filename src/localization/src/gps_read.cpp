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
#include <math.h>
#define ENABLE_SERIAL_LOG 1

//void signal_callback_handler(int signum);

GpsReader::GpsReader() {
	if (ENABLE_SERIAL_LOG) {
		time_t rawtime;
		char name_buffer[80];
		std::time(&rawtime);
		std::tm time_tm;
		localtime_r(&rawtime, &time_tm);
		strftime(name_buffer, 80, "/home/nvidia/tmp/gps_log__%F_%H%M%S.csv", &time_tm);
		log_file_ = fopen(name_buffer, "w");
		if (log_file_ == nullptr) {
			std::cout << "Fail to open file:" << name_buffer << std::endl;
		}
		if (log_file_ != nullptr) {
			fprintf(log_file_, "%s %s %s %s\r\n",
					"time",
                    "theta",
					"Longitude",
					"Lattitude");
			fflush(log_file_);
		}
	}
}


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


bool GpsReader::StartReadGps(){
    using namespace std;
    ros::Rate loop_rate(READ_HZ);
    if(InitSerial() == false){
        return false; 
    }
    else{
        cout <<  "serial init success" << endl;
    }
    FILE * file = fopen("/home/nvidia/tmp/buffoutput.csv","w");
    //serial_port = gps_read.serial_port;

    cout << "this thread number is " << this_thread::get_id()<< endl;
    while(ros::ok()){

        char buffer[1024];
        memset(buffer,0, sizeof(buffer));
        int n;
        //rw_mutex_.lock();
        if((n = read(serial_port, &buffer, sizeof(buffer)) )> 1000){
            //printf
            GPS_STR_.assign(buffer);
	    fprintf(file,"%s",buffer);	
        }
        else if ( n < 0) {
            perror("read serial");
        }
	        if(!(imu_report_.IMU_RECEIVE && gps_report_.GPS_RECEIVE)){
            rw_mutex_.unlock();
            usleep(20000);
            continue;
        }
        //rw_mutex_.unlock();
        loop_rate.sleep();
    }
    if(CloseSerial() == false){
        cout << "serial close error" << endl;
        return false;
    }
    return true;
}

void GpsReader::StartReadGps_fake(){
    using namespace std;
    if(InitSerial() == 0 ){
        return ;
    }
    FILE * file = fopen("/home/nvidia/tmp/buffoutput.csv","w");
    ros::Rate loop_rate(50);
        ros::Publisher pub_to_GPSINFO = n_.advertise<localization::gps>("GPS_INFO",1000);
    while(ros::ok()){
        char buffer[1024];
        memset(buffer,0, sizeof(buffer));
        int n;
        if((n = read(serial_port, &buffer, sizeof(buffer)) ) > 0){
            GPS_STR_.assign(buffer);
            fprintf(file,"%s",buffer);	
        }
        else if ( n < 0) {
            perror("read serial");
        }
        GetOneFrame();
        long now_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		double now_in_seconds = static_cast<double> (now_in_nanoseconds * 1e-9);
        if (ENABLE_SERIAL_LOG && log_file_ != nullptr) {
			fprintf(log_file_,
			        "%.6f %s %s %s \r\n",
					now_in_seconds,gps_report_.Heading.c_str(),gps_report_.Longitude.c_str() , gps_report_.Lattitude.c_str());
		}
	if(!(imu_report_.IMU_RECEIVE && gps_report_.GPS_RECEIVE)){
            rw_mutex_.unlock();
            usleep(20000);
            continue;
        }
        localization::gps msg;
        ROS_INFO("localization ok");
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
        msg.x = y_;
        msg.y = x_;

        ROS_INFO("x is %lf",y_);
        ROS_INFO("y is %lf",x_);
        
        pub_to_GPSINFO.publish(msg);
        //rw_mutex_.unlock();
        loop_rate.sleep();

    }
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
    using namespace std;
    ros::Rate loop_rate(SEND_HZ);
    ros::Publisher pub_to_GPSINFO = n_.advertise<localization::gps>("GPS_INFO",1000);
    while(ros::ok()){
        //lock
        rw_mutex_.lock();
        GetOneFrame();
        if(!(imu_report_.IMU_RECEIVE && gps_report_.GPS_RECEIVE)){
            rw_mutex_.unlock();
            usleep(20000);
            continue;
        }
        localization::gps msg;
        ROS_INFO("localization ok");
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
        msg.x = x_;
        msg.y = y_;

        ROS_INFO("x is %lf",x_);
        ROS_INFO("y is %lf",y_);
        
        pub_to_GPSINFO.publish(msg);

		long now_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		double now_in_seconds = static_cast<double> (now_in_nanoseconds * 1e-9);
        if (ENABLE_SERIAL_LOG && log_file_ != nullptr) {
		fprintf(log_file_,
			"%.6f %s %s %s \r\n",
		        now_in_seconds,gps_report_.Heading.c_str(),gps_report_.Longitude.c_str() , gps_report_.Lattitude.c_str());
	    }

        //unlock
        rw_mutex_.unlock();
        loop_rate.sleep();
        
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

//get one frame of GPFPD and GTIMU
void GpsReader::GetOneFrame(){
    using namespace std;
    
    //both GPFPD and GTIMU start with '$' and end with '\n',we need get a frame contain  GPFPD and GTIMU
   
    auto begin = find(GPS_STR_.begin(),GPS_STR_.end(),'$');
    auto end = find(begin,GPS_STR_.end(),'\n');
    int flagGP = 0;
    int flagGT = 0;
    //if we get both GPFPD and GTIMU or there is no enough info in buff (GPS_STR_) we break the loop
    while((flagGP == 0 || flagGT == 0) && begin != GPS_STR_.end() && end != GPS_STR_.end()){
        string FrameData(begin,end); //FrameData is one GPFPD or GTIMU message
        //cout << FrameData << endl;
        //if(CheckSum(FrameData)){
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
                gps_report_.GPS_RECEIVE = true;
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
                imu_report_.IMU_RECEIVE = true;
            }
 	        if(gps_report_.GPS_RECEIVE == true){
		        double B = stod(gps_report_.Lattitude);  //纬度
		        double L = stod(gps_report_.Longitude);  //经度
		        x_ = getGPFPD_Pos_x0(L, B);
		        y_ = getGPFPD_Pos_y0(L, B);	    
            }
       // }
        GPS_STR_.erase(GPS_STR_.begin(),end + 1); //delete info we have used in buff
        begin = find(GPS_STR_.begin(),GPS_STR_.end(),'$');
        end = find(begin,GPS_STR_.end(),'\n');
    }
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



double GpsReader::getGPFPD_Pos_y0(double L, double B) //y0坐标转换
{


	double a = 6378137.0000;       //长轴
	double b = 6356752.3142451795; //短轴
	double alpha = 0.003352810664747; //扁率
	double e1 = 0.081819190842621;  //第一偏心率
	double e2 = 0.082094437949695;  //第二偏心率
	double radL = rad(L);
	double radB = rad(B);

	double radL0 = rad(6 * round((L + 3) / 6) - 3);
	double l = radL - radL0;
	double radl = rad(l);
	double t = tan(radB);
	double N = a / sqrt(1 - pow(e1, 2) * pow(sin(radB), 2));
	double yita = e2 * cos(radB);

	double GPFPD_Pos_y = l * N*cos(radB) + pow(l, 3) / 6 * N * pow(cos(radB), 3)*(1 - pow(t, 2) + pow(yita, 2)) + pow(l, 5) / 120 * N * pow(cos(radB), 5)*(5 - 18 * pow(t, 2) + pow(t, 4) + 14 * pow(yita, 2) - 58 * pow(yita, 2)* pow(t, 2));
	return GPFPD_Pos_y;
}


double GpsReader::getGPFPD_Pos_x0(double L, double B)    //x0坐标转换
{
	double a = 6378137.0000;       //长轴
	double b = 6356752.3142451795; //短轴
	double alpha = 0.003352810664747; //扁率
	double e1 = 0.081819190842621;  //第一偏心率
	double e2 = 0.082094437949695;  //第二偏心率

	double radL = rad(L);
	double radB = rad(B);

	double radL0 = rad(6 * round((L + 3) / 6) - 3);
	double l = radL - radL0;
	double t = tan(radB);
	double N = a / sqrt(1 - pow(e1, 2) * pow(sin(radB), 2));
	double yita = e2 * cos(radB);

	double c = pow(a, 2) / b;
	double beta0 = 1 - 3 / 4 * pow(e2, 2) + 45 / 64 * pow(e2, 4) - 175 / 256 * pow(e2, 6) + 11025 / 16384 * pow(e2, 8);
	double beta2 = beta0 - 1;
	double beta4 = 15 / 32 * pow(e2, 4) - 175 / 384 * pow(e2, 6) + 3675 / 8192 * pow(e2, 8);
	double beta6 = -35 / 96 * pow(e2, 6) + 735 / 2048 * pow(e2, 8);
	double beta8 = 315 / 1024 * pow(e2, 8);
	double X = c * (beta0 * radB + sin(radB) * (beta2 * cos(radB) + beta4 * pow(cos(radB), 3) + beta6 * pow(cos(radB), 5) + beta8 * pow(cos(radB), 7)));
	double GPFPD_Pos_x = X + pow(l, 2) / 2 * N * sin(radB) * cos(radB)
		+ pow(l, 4) / 24 * N * sin(radB) * pow(cos(radB), 3) * (5 - pow(t, 2) + 9 * pow(yita, 2) + 4 * pow(yita, 4))
		+ pow(l, 6) / 720 * N * sin(radB) * pow(cos(radB), 5) * (61 - 58 * pow(t, 2) + pow(t, 4));
	return GPFPD_Pos_x;
}

double GpsReader::rad(double d)  //角度转弧度
{
	return d * M_PI / 180.0;
}
