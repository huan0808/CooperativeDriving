#pragma once

#include <linux/can.h>

#include "control_by_wire.hpp"
#include "steering_control.hpp"

class ControlSender {
// This class communicates with canbus and send control command.
public:
    ControlSender() = default;
    ~ControlSender() = default;
    bool InitSocket();
    void ControlSteerAngle(const double steering_wheel_angle);
    void ControlSteerTorque(const double steering_wheel_torque);
    void ControlAccel(const double accel_command);
    bool CloseSocket(); 
private:
    int s_ = 0;

    void SendSteerControl(const SteeringControl& steer_control);
    void SendControlByWire(const ControlByWire& control_by_wire);
    void SteeringControlToCanFrameData(const SteeringControl& steer_control,
                                       can_frame* const frame);
    void ControlByWireToCanFrameData(const ControlByWire& steer_control,
                                     can_frame* const frame);
};
