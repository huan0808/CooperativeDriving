#pragma once
#include "gps_report.hpp"
#include <mutex>
#include <thread>
#include "ros/ros.h"

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
    //int GPS_Data_Check(string hex_n,int dex);
    std::string GPS_STR;
    std::mutex rw_mutex;
    ImuReport imu_report;
    GpsReport gps_report;
    ros::NodeHandle n;
    ros::Rate loop_rate = SEND_HZ;
};