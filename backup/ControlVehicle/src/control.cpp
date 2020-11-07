#include "ros/ros.h"
#include "CAN/frame.h"
#include "Serial/String.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <boost/thread.hpp>
#include "canStruct.hpp"

using namespace std;

class VehicleControl
{
public:
    VehicleControl(int rate ,int buff1,int buff2):loop_rate(rate){
    /* 
       如果接收的速率很慢会存进缓冲区里
       如果接收的速率很快会但是发送的频率很慢那么就没有数据
       发布的频率过高的话会存进缓冲区，执行回调函数会将缓冲区一起处理，并且清空缓冲区
    */
        sub1 = n.subscribe("CAN", buff1, &ReceiveInfo::CANReceive, this);
        sub2 = n.subscribe("Serial", buff2, &ReceiveInfo::SerialReceive, this);
    }

    void CANReceive(const CAN::frame::ConstPtr& msg);
    void SerialReceive(const Serial::String::ConstPtr& msg);
    void receive();
private:
    ros::NodeHandle n;
    ros::Rate loop_rate;
    ros::Subscriber sub1;
    ros::Subscriber sub2;
    int frame = 0;
};

void VehicleControl::receive()
{
    while(ros::ok())
    {
        frame++;
        cout << frame << endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
}


void VehicleControl::CANReceive(const CAN::frame::ConstPtr& msg)
{
    ROS_INFO("I heard [%s]",msg->data.c_str());
}

void VehicleControl::SerialReceive(const Serial::String::ConstPtr& msg)
{
    ROS_INFO("I heard [%s]",msg->data.c_str());
}


