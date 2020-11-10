#pragma once
#include <ros/ros.h>
#include <boost/thread.hpp>



class MsgReceive
{
public:
    VehicleControl(int rate ,int buff1,int buff2):loop_rate(rate){
    /* 
       如果接收的速率很慢会存进缓冲区里
       如果接收的速率很快会但是发送的频率很慢那么就没有数据
       发布的频率过高的话会存进缓冲区，执行回调函数会将缓冲区一起处理，并且清空缓冲区
    */
        sub1 = n_.subscribe("CAN_INFO", buff1, &ReceiveInfo::CANReceive, this);
        sub2 = n_.subscribe("Serial_INFO", buff2, &ReceiveInfo::SerialReceive, this);
    }

    void CANReceive(const canbus::frame::ConstPtr& msg);
    void SerialReceive(const localization::gps::ConstPtr& msg);
    void receive();
private:
    ros::NodeHandle n_;
    ros::Rate loop_rate_;
    ros::Subscriber subCan_;
    ros::Subscriber subSerial_;
};
