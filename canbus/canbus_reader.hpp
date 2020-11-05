#pragma once

#include "chassis_report.hpp"
#include "steering_report.hpp"

class CanBusReader {
public:
    CanBusReader() = default;
    ~CanBusReader() = default;
    bool read_steering_report(SteeringReport* const steering_report);
    bool read_chassis_report(ChassisReport* const chassis_report);
private:
    /* data */
};
