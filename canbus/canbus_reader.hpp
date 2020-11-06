#pragma once

#include <linux/can.h>

#include "chassis_report.hpp"
#include "steering_report.hpp"

class CanBusReader {
public:
    CanBusReader() = default;
    ~CanBusReader() = default;
    bool InitSocket();
    bool ReadCanBus(SteeringReport* const steering_report, ChassisReport* const chassis_report);
    bool CloseSocket();
private:
    int s_ = 0;
    void PrintCanFrameDLC(const can_frame& frame);
    void PrintSteeringReport(const SteeringReport& steering_report);
    void PrintVehicleInfo(const ChassisReport& chassis_report);
    void PrintSInfo2(const ChassisReport& chassis_report);
};
