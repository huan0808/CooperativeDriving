#pragma once

#include <stdio.h>
#include <linux/can.h>

#include "chassis_report.hpp"
#include "steering_report.hpp"
#include "ros/ros.h"
#include <mutex>
#include <bitset>

#define SEND_HZ 50   
#define READ_HZ 400
class Perception {
public:
    Perception();
    ~Perception();
    bool InitSocket();
    //int ReadCanBus(SteeringReport* steering_report, ChassisReport* const chassis_report);
    bool CloseSocket();
    void PublishToRos();
  
    //void PublishToRos(const SteeringReport* const steering_report ,const ChassisReport* const chassis_report);
    void StartRead();
private:
    int s_ = 0;
    std::string can_port_;
    void PrintCanFrameDLC(const can_frame& frame);
    //void PrintSteeringReport(const SteeringReport& steering_report);
    void PrintSteeringReport();
    //void PrintVehicleInfo(const ChassisReport& chassis_report);
    void PrintVehicleInfo();
    //void PrintSInfo2(const ChassisReport& chassis_report);
    void PrintSInfo2();
    bool ReadCanBus();
    bool DataCheck(const can_frame& frame);
    //void ConvertData2BitSet(const can_frame& frame,bitset<64> &bit_array);
    ros::NodeHandle n_;
    MoveableTarget move_target_;
    StationTarget station_target_;
    std::mutex rw_mutex_;
 
    FILE* log_file_ = nullptr;
    bool HSEVHU_SR_read_ = false;
    bool HSEVCO_VI_read_ = false;
    bool HSEVCO_SI2_read_ = false;
};
