#pragma once

#include <linux/can.h>

#include "chassis_report.hpp"
#include "steering_report.hpp"
#include "ros/ros.h"
#include <mutex>


#define CANBUS_T 0.01 // in seconds TODO(huan)：统一定义成Hz吧，频率可能要调高点
#define SEND_HZ 100

class CanBusReader {
public:
    CanBusReader() = default;
    ~CanBusReader() = default;
    bool InitSocket();
    //int ReadCanBus(SteeringReport* steering_report, ChassisReport* const chassis_report);
    bool ReadCanBus(); //TODO(huan): 由于现在main调用的是StartRead，因此这个可以变成私有成员函数了
    bool CloseSocket();
    void PublishToRos();
    //void PublishToRos(const SteeringReport* const steering_report ,const ChassisReport* const chassis_report);
    void StartRead();
private:
    int s_ = 0;
    void PrintCanFrameDLC(const can_frame& frame);
    //void PrintSteeringReport(const SteeringReport& steering_report);
    void PrintSteeringReport();
    //void PrintVehicleInfo(const ChassisReport& chassis_report);
    void PrintVehicleInfo();
    //void PrintSInfo2(const ChassisReport& chassis_report);
    void PrintSInfo2();
    bool DataCheck(const can_frame& frame);
    ros::NodeHandle n;
    SteeringReport steering_report; //TODO(huan): 一个好的编程习惯是将私有成员变量命名以_结尾，所以这个变量名写成steering_report_，其他类似
    ChassisReport chassis_report;
    std::mutex rw_mutex;
    ros::Rate loop_rate = SEND_HZ;
};
