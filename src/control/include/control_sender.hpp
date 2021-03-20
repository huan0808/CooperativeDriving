#pragma once
#include "canbus/frame.h"
#include "localization/gps.h"
#include <linux/can.h>
#include "ros/ros.h"
#include "control_by_wire.hpp"
#include "steering_control.hpp"
#include <mutex>
#include "vehicle_info.hpp" 

#define RECEIVE_HZ 50
#define WRITE_HZ 50 
#define CONTROL_T 0.02


class ControlSender {
// This class communicates with canbus and send control command.
public:
    ControlSender();
    ~ControlSender() = default;
    //send to CANBUS
    bool InitSocket();
    void ControlSteerAngle(const double steering_wheel_angle);
    void ControlSteerTorque(const double steering_wheel_torque);
    void ControlAccel(const double accel_command);
    bool CloseSocket(); 
    bool StartWrite();
    //receive from ros
    void CANReceive(const canbus::frame::ConstPtr& msg);
    void SerialReceive(const localization::gps::ConstPtr& msg);
    void StartReceive();
    void SendResetFrame();
    void log();
private:
    int s_ = 0;

    void SendSteerControl(const SteeringControl& steer_control);
    void SendControlByWire(const ControlByWire& control_by_wire);
    void SteeringControlToCanFrameData(const SteeringControl& steer_control,
                                       can_frame* const frame);
    void ControlByWireToCanFrameData(const ControlByWire& steer_control,
                                     can_frame* const frame);
    

    ros::NodeHandle n_;
    ros::Rate loop_rate_ = RECEIVE_HZ;
    ros::Subscriber subCan_;
    ros::Subscriber subSerial_;
    std::mutex rw_lock_;
    VehicleInfo vehicle_info_;
    FILE* log_file_;
    int path_point_index_log_;
    double lat_log_ = -99.0;
    double head_log_ = -99.0;
    double torque = -99.0;
    double ref_heading = -99.0;
    int index_ = -99;
};
