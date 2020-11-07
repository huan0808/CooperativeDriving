/***********************************************************/
/*
    Function:ROS parsing GPS agreement(GPFPD)，Post to topic.
    Author:YuTeng
    Date:2019/10/14
    Version: V1.0
*/
/***********************************************************/
#include "ros/ros.h"
#include "gps/gps_gtimu.h"
#include <serial/serial.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std; 
int IMU_Data_Check(uint8_t a[],int length);
int GPS_Data_Check(string hex_n,int dex);
int main(int argc,char ** argv)
{
    ros::init(argc,argv,"gps_gtimu"); //解析参数，命名节点
    ros::NodeHandle nh; //创建句柄，实例化node
    gps::gps_gtimu msg; //创建gps消息
    serial::Serial sp;
    ros::Publisher pub = nh.advertise<gps::gps_gtimu>("gps_gtimu",1); //创建publisherW  
    ros::Rate loop_rate(1.0); //定义循环发布的频率
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyACM0");
    //设置串口通信的波特率
    sp.setBaudrate(115200);
    //窗口设置timeout
    sp.setTimeout(to);
    try
    {
         //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }

    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyACM0 is opened.");
    }
    else
    {
        return -1;
    }
    
    clock_t startTime,endTime;    
    while(ros::ok())
    {
        startTime = clock();//计时开始
        size_t n = sp.available();
        string str;
        string IMU_Header;
		string IMU_GPSWeek;
		string IMU_GPSTime;
		string GyroX;
		string GyroY;
		string GyroZ;
		string AccX;
		string AccY;
		string AccZ;
		string Tpr;
		string IMU_Cs;
		string IMU_CrLf;
        uint8_t buffer[1024];
        int num=0;
        int flag=0;
        n = sp.read(buffer, n);
        if(n>0)
        {
            if(IMU_Data_Check(buffer,n)==0)//如果校验不通过则跳过
            {
                continue;
            }
            for(int j=0; j<n; j++)
            {
                if(buffer[j]==',')
                {
                    num++;
                }
                else 
                {
                    if(num==0)
                    {
                        IMU_Header+=buffer[j];  
                    }
                    else if(num==1)
                    {
                        IMU_GPSWeek+=buffer[j];
                    }
                    else if(num==2)
                    {
                        IMU_GPSTime+=buffer[j];
                    }
                    else if(num==3)
                    {
                        GyroX+=buffer[j];
                    }
                    else if(num==4)
                    {
                        GyroY+=buffer[j];
                    }
                    else if(num==5)
                    {
                        GyroZ+=buffer[j];
                    }
                    else if(num==6)
                    {
                        AccX+=buffer[j];
                    }
                    else if(num==7)
                    {
                        AccY+=buffer[j];
                    }
                    else if(num==8)
                    {
                        AccZ+=buffer[j];
                    }
                    else if(num==9)
                    {
		    			
                        if(buffer[j]=='*')
                        {
							flag++;
                        }
						if(flag==0)
		    			{
							Tpr+=buffer[j];
		    			}
                        if(flag>0&&flag<4)
                        {
                            IMU_Cs+=buffer[j];
							flag++;
                        }
                        if(flag>4)
                        {
                            IMU_CrLf+=buffer[j];
                        }    
                        
                    }
                }//else
			
            str+=buffer[j];
            }//for
               
            msg.IMU_Header=IMU_Header;
            msg.IMU_GPSWeek=IMU_GPSWeek;
            msg.IMU_GPSTime=IMU_GPSTime;
            msg.GyroX=GyroX;
            msg.GyroY=GyroY;
            msg.GyroZ=GyroZ;
            msg.AccX=AccX;
            msg.AccY=AccY;
            msg.AccZ=AccZ;
            msg.Tpr=Tpr;
            msg.IMU_Cs=IMU_Cs;
            msg.IMU_CrLf=IMU_CrLf;
            //std::cout <<"GTIMU:   "<<str<< std::endl;
            ROS_INFO("IMU_Header:%s",msg.IMU_Header.c_str());
            ROS_INFO("IMU_GPSWeek:%s",msg.IMU_GPSWeek.c_str());
            ROS_INFO("IMU_GPSTime:%s",msg.IMU_GPSTime.c_str());
            ROS_INFO("GyroX:%s",msg.GyroX.c_str());
            ROS_INFO("GyroY:%s",msg.GyroY.c_str());
            ROS_INFO("GyroZ:%s",msg.GyroZ.c_str());
            ROS_INFO("AccX:%s",msg.AccX.c_str());
            ROS_INFO("AccY:%s",msg.AccY.c_str());
            ROS_INFO("AccZ:%s",msg.AccZ.c_str());
            ROS_INFO("Tpr:%s",msg.Tpr.c_str());
            ROS_INFO("IMU_Cs:%s",msg.IMU_Cs.c_str());
            ROS_INFO("IMU_CrLf:%s",msg.IMU_CrLf.c_str());
            pub.publish(msg); //发布消息
            sp.write(buffer, n);
            endTime = clock();//计时结束
            std::cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
        }
        n=0;
        //loop_rate.sleep(); //根据定义的发布频率，sleep
    }
    sp.close();
    return 0;
}
int IMU_Data_Check(uint8_t a[],int length)//GPS数据校验
{
    int head_n=6;
    string head_str; //帧头
    string CS_str; //数据帧校验位
    int flag=1; //数据标志位
    int CS_dex; 
    unsigned char CS=0;
    int chang=0;
    for(int i=0;i<length-2;i++)
    {
        if(i<head_n)
        {
            head_str+=a[i];
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
    if((head_str=="$GTIMU")&&(GPS_Data_Check(CS_str,CS_dex)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int GPS_Data_Check(string hex_n,int dex)
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
