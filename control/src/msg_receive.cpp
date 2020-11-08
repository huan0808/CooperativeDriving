#include "msg_receive.hpp"

void MsgReceive::receive()
{
    while(ros::ok())
    {
        frame++;
        cout << frame << endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void MsgReceive::CANReceive(const CAN::frame::ConstPtr& msg)
{
    //ROS_INFO("I heard [%s]",msg->data.c_str());
    //TODO
}

void MsgReceive::SerialReceive(const Serial::String::ConstPtr& msg)
{
    //ROS_INFO("I heard [%s]",msg->data.c_str());
    //TODO
}
