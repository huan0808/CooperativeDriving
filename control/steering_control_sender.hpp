#pragma once

#include "steering_control.hpp"

class SteeringControlSender {
// This class communicates with canbus and send steering control command.
public:
    SteeringControlSender() = default;
    ~SteeringControlSender() = default;
    void send_control(const SteeringControl& steer_control);
private:
    /* data */
};
