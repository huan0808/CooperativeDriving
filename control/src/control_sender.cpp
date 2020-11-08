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
#define HANDTORQUE_LIMIT 5

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
    //SteeringAngle in -500-500 deg
    steering_control.SC_TargetSteeringAngle = -1.0 * steering_wheel_angle; 
    //SteeringSpeed in 200-400 deg/s
    steering_control.SC_TargetSteeringSpeed = 200.0;
    steering_control.SC_SetHandTorqueLimitValid = 1;
   
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT;
    SendSteerControl(steering_control);
}

void ControlSender::ControlSteerTorque(const double steering_wheel_torque) {
    // steering_wheel_torque > 0 means turning left
    SteeringControl steering_control;
    steering_control.SC_SteeringControlRequest = 1;
    //torque in 2-5 NM
    steering_control.SC_TargetTorque = std::fabs(steering_wheel_torque); 
    steering_control.SC_TargetTorqueSign = steering_wheel_torque < 0 ? 1 : 0;
    steering_control.SC_SetHandTorqueLimitValid = 1;
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT; 
    SendSteerControl(steering_control);
}

void ControlSender::ControlAccel(const double accel_command) {
    ControlByWire control_by_wire;

    // TODO(huan): any upper and lower limit?
    //upper limit may be this car's physical limit
    control_by_wire.CBW_AX_Request = accel_command; 

    control_by_wire.CBW_AccelerationRequestSt = 1;
    control_by_wire.CBW_FunctionRequestSt = 1;
    SendControlByWire(control_by_wire);
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
    ControlByWireToCanFrameData(control_by_wire, &frame);
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
    if(steer_control.SC_SteeringControlRequest == 0){
        frame->data[1] = 0x00; 
    }
    else if(steer_control.SC_SteeringControlRequest == 1){
        frame->data[1] = 1;
       
        int tsa = steer_control.SC_TargetSteeringAngle + 600;

        //GET tsa low 4 bits
        frame->data[1] |= (tsa << 4); 

        //GET tsa high 7 bits
        frame->data[2] |= (tsa >> 4);


        int tss = steer_control.SC_TargetSteeringSpeed;
        //GET tss low 1 bits
        frame->data[2] |= ((tss & 1) << 7);
        //GET tss high 8 bits
        frame->data[3] |= (tss >> 1);
    }
    else if(steer_control.SC_SteeringControlRequest == 2){
        frame->data[1] = 2;
        
        int tt = steer_control.SC_TargetTorque * 100;
        //GET tt low 8 bits
        frame->data[4] |= tt;
        //GET tt high 2 bits
        frame->data[5] |= (tt >> 8);
        //set targettorque sign
        frame->data[5] |= (steer_control.SC_TargetTorqueSign << 2);

    }
    else{
        std::cout << "Request error" << std::endl;
        return; 
    }

    frame->data[5] |= (steer_control.SC_SetHandTorqueLimitValid << 5);
    int htl = steer_control.SC_SetHandTorqueLimit * 100;
    frame->data[5] |= (htl << 6);
    frame->data[6] |= (htl >> 2);
    
    //DataCheck
    for(int i = 1; i < 8; i++)
    {
        frame->data[0] ^= frame->data[i];
    }
}

void ControlSender::ControlByWireToCanFrameData(
    const ControlByWire& control_by_wire, can_frame* const frame) {
    int ax = (control_by_wire.CBW_AX_Request + 20) * 100;
    frame->data[1] |= ax;
    frame->data[2] |= (ax >> 8);

    frame->data[2] |= (control_by_wire.CBW_AccelerationRequestSt << 4);
    frame->data[2] |= (control_by_wire.CBW_FunctionRequestSt << 6); 
  

    //DataCheck
    for(int i = 1; i < 8; i++)
    {
        frame->data[0] ^= frame->data[i];
    }
}