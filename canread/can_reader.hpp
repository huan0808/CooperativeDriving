#pragma once

#include "chassis_report.hpp"
#include "steering_report.hpp"

class CanReader {
public:
    CanReader() = default;
    ~CanReader() = default;
    void read_steering_report(SteeringReport* const steering_report);
    void read_chassis_report(ChassisReport* const chassis_report);
private:
    /* data */
};
