#include "control_sender.hpp"
#include <chrono>
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

#include <thread>
#include "lat_controller.hpp"
#include "lon_controller.hpp"

#define HSEVHU_SC_ID 0x501
#define HSEVCO_CBW_ID 0x5C0
#define HANDTORQUE_LIMIT 5
#define ENABLE_LOG 1

ControlSender::ControlSender(){
    if (ENABLE_LOG) {
		time_t rawtime;
		char name_buffer[80];
		std::time(&rawtime);
		std::tm time_tm;
		localtime_r(&rawtime, &time_tm);
		strftime(name_buffer, 80, "/home/nvidia/tmp/vehicle_log__%F_%H%M%S.csv", &time_tm);
		log_file_ = fopen(name_buffer, "w");
		if (log_file_ == nullptr) {
			std::cout << "Fail to open file:" << name_buffer << std::endl;
		}
		if (log_file_ != nullptr) {
			fprintf(log_file_, "%s %s %s %s %s %s %s\r\n",
					"time",
					"x",
					"y",
                    "theta",
                    "speed",
                    "steer_angle",
                    "front_steering_angle");
			fflush(log_file_);
		}
	}

}

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
        frame->data[1] = 0; 
    }
    else if(steer_control.SC_SteeringControlRequest == 1){
        frame->data[1] = 1;
        
        int tt = steer_control.SC_TargetTorque * 100;
        //GET tt low 8 bits
        frame->data[4] |= tt;
        //GET tt high 2 bits
        frame->data[5] |= (tt >> 8);
        //set targettorque sign
        frame->data[5] |= (steer_control.SC_TargetTorqueSign << 2);

    }    
    else if(steer_control.SC_SteeringControlRequest == 2){
        frame->data[1] = 2;
       
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
    
    //light control
    /*        
        frame->data[1] =0xD0;
        frame->data[2] =0x47;
        frame->data[6]  =0x20;
    */
    //acc control
    //frame->data[0] = 0x36;
    // frame->data[1] =0xDA;
    // frame->data[2] =0x57;
    // frame->data[5] = 0x40;
    
    frame->data[1] |= ax;
    frame->data[2] |= (ax >> 8);
    frame->data[2] |= (control_by_wire.CBW_AccelerationRequestSt << 4);
    frame->data[2] |= (control_by_wire.CBW_FunctionRequestSt << 6); 
    frame->data[5] = 0x40; 
   
    //DataCheck
    /*
        for(int i = 1; i < 8; i++)
        {
            frame->data[0] ^= frame->data[i];
        }
    */
}

void ControlSender::SendResetFrame(){
    can_frame frame;
	memset(frame.data, 0, sizeof(frame.data));


	frame.can_id = HSEVCO_CBW_ID;
	frame.can_dlc = 8;
	frame.data[1] =0xDA;
	frame.data[2] =0x07;

    //frame.data[2] =0x07;
    /*
    frame.data[3] = 0;
    frame.data[4] = 0;
    */
    for(int i = 0; i < 100; i++ ){
        write(s_, &frame, sizeof(can_frame)); 
        usleep(20000);
    }
  
}

bool ControlSender::StartWrite(){
    using namespace std;
    ros::Rate loop_rate(WRITE_HZ);
    if (!InitSocket()) {
        cout << "Init socket failed" << endl;
        return false;
    } else {
        cout << "Init socket success" << endl;
    }
    
    LatController lat_controller;
    LonController lon_controller;
    lon_controller.SetCruiseSpeed(15.0); // set cruise speed [km/h]
    SendResetFrame();
    while (ros::ok) {
        rw_lock_.lock();
        if(!(vehicle_info_.FLAG_SERIAL && vehicle_info_.FLAG_CAN)){ 
            ROS_INFO("hasn't receive vehicle info");
            rw_lock_.unlock();
            usleep(20000);
            continue;
        }
        const double steering_angle_command = -100.0;
        //ControlSteerAngle(steering_angle_command);
        const double accel_command = lon_controller.ComputeAccel(vehicle_info_.speed/3.6, CONTROL_T);
        ControlAccel(accel_command);
        const double steer_torque_command = lat_controller.ComputeSteerTorque(
            vehicle_info_.x, vehicle_info_.y, vehicle_info_.theta, vehicle_info_.steer_angle);
        ControlSteerTorque(steer_torque_command);
        //const double torque_command = 3;
        //ControlSteerTorque(torque_command);
        
        rw_lock_.unlock();
        loop_rate.sleep();
    }

    if (!CloseSocket()) {
        cout << "Close socket failed" << endl;
        return false;
    } else {
        cout << "Close socket succuss" << endl;
    }   

}


//receive from ros
void ControlSender::CANReceive(const canbus::frame::ConstPtr& msg){
   
    //std::cout << "0" << std::endl;
    vehicle_info_.speed = msg->VI_VehicleSpeed;
    vehicle_info_.steer_angle = msg->SR_CurrentSteeringAngle;
    vehicle_info_.front_steering_angle = msg->VI_FrontSteeringAngle;
    vehicle_info_.FLAG_CAN = 1;
  
}

void ControlSender::SerialReceive(const localization::gps::ConstPtr& msg){
   
    //std::cout << "1" <<std::endl;
    vehicle_info_.x = msg->x;
    vehicle_info_.y = msg->y;
    vehicle_info_.theta = stod(msg->Heading);
    vehicle_info_.FLAG_SERIAL = 1;
  
}

void ControlSender::StartReceive(){
    subCan_=n_.subscribe("CAN_INFO",1000,&ControlSender::CANReceive,this);
    subSerial_ = n_.subscribe("GPS_INFO",1000,&ControlSender::SerialReceive,this);
    ros::Rate loop_rate(RECEIVE_HZ);
    while(ros::ok())
    {
        rw_lock_.lock();
        //frame++;
        //ROS_INFO("this is %d frame",frame);
        ros::spinOnce();
	    if(vehicle_info_.FLAG_CAN && vehicle_info_.FLAG_SERIAL){
        	long now_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		    double now_in_seconds = static_cast<double> (now_in_nanoseconds * 1e-9);
            if(ENABLE_LOG && log_file_ != nullptr){
                fprintf(log_file_,"%.6f %.2f %.2f %.2f %.2f %.2f %.2f\r\n",
                now_in_seconds, vehicle_info_.x,vehicle_info_.y,
                vehicle_info_.theta,vehicle_info_.speed,
                vehicle_info_.steer_angle,
                vehicle_info_.front_steering_angle);
            }
        }
        rw_lock_.unlock();
        loop_rate_.sleep();
    }
}


