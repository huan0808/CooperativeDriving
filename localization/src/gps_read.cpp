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
using namespace std;
bool GpsReader::InitSerial(){

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
//how to make sure we don't miss  frames

int GpsReader::ReadGps(GpsReport* const gps_report){
    char buffer[1024];
    memset(buffer,0, sizeof(buffer));
    
    int n = read(serial_port, &buffer, sizeof(buffer));

    if ( n < 0) {
        perror("read");
        return 2;
    }
    if(FPD_Data_Check(buffer,n) == 0)//如果校验不通过则跳过
    {
        return 1;
    }
    GPS_STR += string(buffer);
    int num = 0;
    vector<string> gps_info;
    string temp;
    int flag = 0;
    for(int i = 0; i < 1024; i++)
    {
        if(flag == 1 && buffer[i] == '\r\n'){
            
            //cout << buffer[i];
            break;
        }
        if(buffer[i] == '$'){
            flag = 1;
        }
        if(flag){
            if(buffer[i] == ','){
                gps_info.push_back(temp);
                temp.clear();
            }
            else{
                temp += buffer[i];
            }
            
        }
        
    }
    int n = 0;
    gps_report->FPD_Header = gps_info[n++];
    gps_report->FPD_GPSWeek = gps_info[n++];
    gps_report->FPD_GPSTime = gps_info[n++];
    gps_report->Heading = gps_info[n++];
    gps_report->Pitch = gps_info[n++];
    gps_report->Roll = gps_info[n++];
    gps_report->Lattitude = gps_info[n++];
    gps_report->Lattitude = gps_info[n++];
    gps_report->Longitude = gps_info[n++];
    gps_report->Altitude = gps_info[n++];
    gps_report->Ve = gps_info[n++];
    gps_report->Vn = gps_info[n++];
    gps_report->Vu = gps_info[n++];
    gps_report->Baseline = gps_info[n++];
    gps_report->NSV1 = gps_info[n++];
    gps_report->NSV2 = gps_info[n++];

    gps_report->Status = gps_info[n][1];

    return 0;
}


bool GpsReader::CloseSerial(){
    if(close(serial_port) == -1){
        cout << "close error" << endl;
        return false;
    }
    return true;
}
int GpsReader::FPD_Data_Check(char a[],int length)//GPS数据校验
{
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