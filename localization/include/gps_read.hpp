#pragma once

#include "gps_report.hpp"

class GpsReader{
public:
    GpsReader() = default;
    ~GpsReader() = default;
    bool InitSerial();
    int ReadGps(GpsReport* const gsp_report);
    bool CloseSerial();
    int serial_port;
private:
    int FPD_Data_Check(char a[],int length);
    int GPS_Data_Check(string hex_n,int dex);
    string GPS_STR;
};