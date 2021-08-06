#pragma once
#include "gps_report.hpp"
#include <mutex>
#include <thread>
#include "ros/ros.h"
#include "string"
#include "localization/gps.h"
#define READ_HZ 20
#define SEND_HZ 50

class GpsReader{

public:
    GpsReader();
    ~GpsReader() = default;
    bool InitSerial();
    bool StartReadGps();
    bool CloseSerial();
    void PublishToRos();
    void StartReadGps_fake();
    int serial_port;
private:
    int FPD_Data_Check(char a[],int length);
    int GPS_Data_Check(std::string &hex_n,int dex);
    bool CheckSum(const std::string& frame);
    void GetOneFrame();
    double getGPFPD_Pos_x0(double L, double B);
    double getGPFPD_Pos_y0(double L, double B);
    std::string GPS_STR_;
    std::mutex rw_mutex_;
    std::string gps_port_;
    bool enable_log_;
    std::string trajectory_file_;
    ImuReport imu_report_;
    GpsReport gps_report_;
    ros::NodeHandle n_;
    FILE* log_file_ = nullptr;
    double rad(double d);  //角度转弧度
    double x_ = -99.0;
    double y_ = -99.0;
    int hz_;
    int serial_port_;
    bool ENABLE_SERIAL_LOG;
};