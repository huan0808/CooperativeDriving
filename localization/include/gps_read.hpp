#pragma once

#include "gps_report.hpp"

class GpsReader{
public:
    GpsReader() = default;
    ~GpsReader() = default;
    bool InitSerial();
    int ReadGps(GpsReport* gsp_report);
    bool CloseSerial();
    int serial_port;
private:
    int FPD_Data_Check(uint8_t a[],int length);
    int GPS_Data_Check(string hex_n,int dex);
};