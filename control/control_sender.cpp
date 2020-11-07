#include "control_sender.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can/raw.h>

#include <cmath>
#include <iostream>
#include <string>

#define HSEVHU_SC_ID 0x501
#define HSEVCO_CBW_ID 0x5C0
#define HANDTORQUE_LIMIT 20.0

bool ControlSender::InitSocket() {
	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket error");
		return false;
	}
	ifreq ifr;
	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);
	sockaddr_can addr;
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind error");
		return false;
	}
    s_ = s;
    return true;
}

void ControlSender::ControlSteerAngle(const double steering_wheel_angle) {
    // steering_wheel_angle > 0 means turning left
    SteeringControl steering_control;
    steering_control.SC_SteeringControlRequest = 2;
    steering_control.SC_TargetSteeringAngle = -1.0 * steering_wheel_angle; // TODO(huan): any upper and lower limit?
    steering_control.SC_TargetSteeringSpeed = 10.0; // TODO(huan): check this speed
    steering_control.SC_SetHandTorqueLimitValid = 1;
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT; // TODO(huan): check this limit
    SendSteerControl(steering_control);
}

void ControlSender::ControlSteerTorque(const double steering_wheel_torque) {
    // steering_wheel_torque > 0 means turning left
    SteeringControl steering_control;
    steering_control.SC_SteeringControlRequest = 1;
    steering_control.SC_TargetTorque = std::fabs(steering_wheel_torque); // TODO(huan): any upper and lower limit?
    steering_control.SC_TargetTorqueSign = steering_wheel_torque < 0 ? 1 : 0;
    steering_control.SC_SetHandTorqueLimitValid = 1;
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT; // TODO(huan): check this limit
    SendSteerControl(steering_control);
}

void ControlSender::ControlAccel(const double accel_command) {
    // TODO(huan): please check if this implementation is correct
    ControlByWire control_by_wire;
    control_by_wire.CBW_AX_Request = accel_command; // TODO(huan): any upper and lower limit?
    control_by_wire.CBW_AccelerationRequestSt = 1;
}

void ControlSender::SendSteerControl(const SteeringControl& steer_control) {
    can_frame frame;
	memset(frame.data, 0, sizeof(frame.data));
  
	frame.can_id = HSEVHU_SC_ID;
	frame.can_dlc = 8;
    SteeringControlToCanFrameData(steer_control, &frame);
    write(s_, &frame, sizeof(can_frame));
}

void ControlSender::SendControlByWire(const ControlByWire& control_by_wire) {
    can_frame frame;
	memset(frame.data, 0, sizeof(frame.data));

	frame.can_id = HSEVCO_CBW_ID;
	frame.can_dlc = 8;
    ControlByWireToCanFrameData(steer_control, &frame);
    write(s_, &frame, sizeof(can_frame));    
}

bool ControlSender::CloseSocket() {
    if (close(s_) < 0) {
        perror("Close error");
        return false;
	}
    return true;
}

void ControlSender::SteeringControlToCanFrameData(
    const SteeringControl& steer_control, can_frame* const frame) {
    //TODO(huan): please implement this method
}

void ControlSender::ControlByWireToCanFrameData(
    const ControlByWire& steer_control, can_frame* const frame) {
    //TODO(huan): please implement this method
}