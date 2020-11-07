/***********************************************************/
/*
    Function:ROS parsing GPS agreement(GPFPD)，Post to topic.
    Author:YuTeng
    Date:2019/10/14
    Version: V1.0
*/
/***********************************************************/

#include "ros/ros.h"
#include "gps/gps_gpfpd.h"
#include <serial/serial.h>
#include <iostream>
#include <string>
#include <ctime>
#incldue <signal.h>
#incldue <cstdlib>
#incldue <unistd.h>

using namespace std; 

serial::Serial sp;


int HexStr2Int(string & hs);
int FPD_Data_Check(uint8_t a[],int length);
int GPS_Data_Check(string hex_n,int dex);
void signal_callback_handler(int signum);
int main(int argc,char ** argv)
{
    ros::init(argc,argv,"gps_gpfpd"); //解析参数，命名节点
    ros::NodeHandle nh; //创建句柄，实例化node
    gps::gps_gpfpd msg; //创建gps消息
   
    ros::Publisher pub = nh.advertise<gps::gps_gpfpd>("gps_gpfpd",1); //创建publisherW  
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
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
    
    clock_t startTime,endTime;

    signal(SIGINT, signal_callback_handler);    

    while(ros::ok())
    {

        startTime = clock();//计时开始
        size_t n = sp.available();
        string str;
        string FPD_Header;
        string FPD_GPSWeek;
        string FPD_GPSTime;
        string Heading;
        string Pitch;
        string Roll;
        string Lattitude;
        string Longitude;
        string Altitude;
        string Ve;
        string Vn;
        string Vu;
        string Baseline;
        string NSV1;
        string NSV2;
        string Status;
        string FPD_Cs;
        string FPD_CrLf;
        uint8_t buffer[1024];
        int num=0;
        int flag=0;
        n = sp.read(buffer, n);
        if(n>0)
        {
            if(FPD_Data_Check(buffer,n)==0)//如果校验不通过则跳过
            {
                continue;
            }
            for(int i=0; i<n; i++)
            {
                if(buffer[i]==',')
                {
                    num++; 
                }
                else 
                {
                    if(num==0)
                    {
                        FPD_Header+=buffer[i];   
                    }
                    else if(num==1)
                    {
                        FPD_GPSWeek+=buffer[i];
                    }
                    else if(num==2)
                    {
                        FPD_GPSTime+=buffer[i];
                    }
                    else if(num==3)
                    {
                        Heading+=buffer[i];
                    }
                    else if(num==4)
                    {
                        Pitch+=buffer[i];
                    }
                    else if(num==5)
                    {
                        Roll+=buffer[i];
                    }
                    else if(num==6)
                    {
                        Lattitude+=buffer[i];
                    }
                    else if(num==7)
                    {
                        Longitude+=buffer[i];
                    }
                    else if(num==8)
                    {
                        Altitude+=buffer[i];
                    }
                    else if(num==9)
                    {
                        Ve+=buffer[i];
                    }
                    else if(num==10)
                    {
                        Vn+=buffer[i];
                    }
                    else if(num==11)
                    {
                        Vu+=buffer[i];
                    }
                    else if(num==12)
                    {
                        Baseline+=buffer[i];
                    }
                    else if(num==13)
                    {
                        NSV1+=buffer[i];
                    }
                    else if(num==14)
                    {
                        NSV2 += buffer[i];
                    }
                    else if(num == 15)
                    {
                        if(flag<2)
                        {
                            Status += buffer[i];
                        }
                        else if(flag>=2&&flag<5)
                        {
                            FPD_Cs+=buffer[i];
                        }
                        else if(flag>=5)
                        {
                            FPD_CrLf+=buffer[i];
                        }
                        flag++;
                    }
                }
                str+=buffer[i];
            }
            msg.FPD_Header=FPD_Header;
            msg.FPD_GPSWeek=FPD_GPSWeek;
            msg.FPD_GPSTime=FPD_GPSTime;
            msg.Heading=Heading;
            msg.Pitch=Pitch;
            msg.Roll=Roll;
            msg.Lattitude=Lattitude;
            msg.Longitude=Longitude;
            msg.Altitude=Altitude;
            msg.Ve=Ve;
            msg.Vn=Vn;
            msg.Vu=Vu;
            msg.Baseline=Baseline;
            msg.NSV1=NSV1;
            msg.NSV2=NSV2;
            msg.Status=Status;
            msg.FPD_Cs=FPD_Cs;
            msg.FPD_CrLf=FPD_CrLf;
            std::cout <<"GPFPD:   "<<str<< std::endl;
            ROS_INFO("FPD_Header:%s",msg.FPD_Header.c_str());
            ROS_INFO("FPD_GPSWeek:%s",msg.FPD_GPSWeek.c_str());
            ROS_INFO("FPD_GPSTime:%s",msg.FPD_GPSTime.c_str());
            ROS_INFO("Heading:%s",msg.Heading.c_str());
            ROS_INFO("Pitch:%s",msg.Pitch.c_str());
            ROS_INFO("Roll:%s",msg.Roll.c_str());
            ROS_INFO("Lattitude:%s",msg.Lattitude.c_str());
            ROS_INFO("Longitude:%s",msg.Longitude.c_str());
            ROS_INFO("Altitude:%s",msg.Altitude.c_str());
            ROS_INFO("Ve:%s",msg.Ve.c_str());
            ROS_INFO("Vn:%s",msg.Vn.c_str());
            ROS_INFO("Vu:%s",msg.Vu.c_str());
            ROS_INFO("Baseline:%s",msg.Baseline.c_str());
            ROS_INFO("NSV1:%s",msg.NSV1.c_str());
            ROS_INFO("NSV2:%s",msg.NSV2.c_str());
            if(HexStr2Int(msg.Status) == 0)
            {
                ROS_INFO("Status: 0 ");
            }
            else if(HexStr2Int(msg.Status) == 1)
            {
                ROS_INFO("Status: 1 ");
            }
            else if(HexStr2Int(msg.Status) == 2)
            {
                ROS_INFO("Status: 2 ");
            }
            else if(HexStr2Int(msg.Status) == 3)
            {
                ROS_INFO("Status: 3 ");
            }
            else if(HexStr2Int(msg.Status) == 4)
            {
                ROS_INFO("Status: 4 ");
            }
            else if(HexStr2Int(msg.Status) == 5)
            {
                ROS_INFO("Status: 5 ");
            }
            else if(HexStr2Int(msg.Status) == 6)
            {
                ROS_INFO("Status: 6 ");
            }
            else if(HexStr2Int(msg.Status) == 7)
            {
                ROS_INFO("Status: 7 ");
            }
            else if(HexStr2Int(msg.Status) == 8)
            {
                ROS_INFO("Status: 8 ");
            }
            else if(HexStr2Int(msg.Status) == 9)
            {
                ROS_INFO("Status: 9 ");
            }
            ROS_INFO("FPD_Cs:%s",msg.FPD_Cs.c_str());
            ROS_INFO("FPD_CrLf:%s",msg.FPD_CrLf.c_str());
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
int FPD_Data_Check(uint8_t a[],int length)//GPS数据校验
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
    if((head_str=="$GPFPD")&&(GPS_Data_Check(CS_str,CS_dex)))
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
int HexStr2Int(string & hs)
{
    int ans = 0;
    for(int i = hs.size() - 1; i >= 0; i-- )
    {
        if(hs[i] >= 'A' && hs[i] <= 'F')
        {
            ans += (hs[i] - 'A' + 10)* pow(16,i);
        }
        else
        {
            ans += (hs[i] - '0')* pow(16,i);
        }
        
    }
    return ans;
}


void signal_callback_handler(int signum) {
   cout << "close the serial "  << endl;

   sp.close();
   // Terminate program
   exit(signum);
}