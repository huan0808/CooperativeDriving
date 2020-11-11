#pragma once
#include "gps_report.hpp"
#include <mutex>
#include <thread>
#include "ros/ros.h"
#include "localization/gps.h"
#define SERIAL_T 0.05
#define SEND_HZ 100
#define READ_T 0.01

class GpsReader{
public:
    GpsReader() = default;
    ~GpsReader() = default;
    bool InitSerial();
    bool StartReadGps();
    bool CloseSerial();
    void PublishToRos();
    int serial_port;
private:
    int FPD_Data_Check(char a[],int length);
    int GPS_Data_Check(string hex_n,int dex);
    bool CheckSum(const std::string& frame);
    std::string GPS_STR_;
    std::mutex rw_mutex_;
    ImuReport imu_report_;
    GpsReport gps_report_;
    ros::NodeHandle n_;
    ros::Rate loop_rate_ = SEND_HZ;
};