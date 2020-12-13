// Date: 20201209 22:24
// version 1.0
// modified by lwy [20201209-22-24]

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
#include "math_utils.hpp"

// can signal ??
#define HSEVHU_SC_ID 0x501
#define HSEVCO_CBW_ID 0x5C0
#define HANDTORQUE_LIMIT 5

// write log switch
#define ENABLE_LOG 1

ControlSender::ControlSender(){
	/*
	* write log header
	*/
    if (ENABLE_LOG) {
		time_t rawtime;
		char name_buffer[80];
		std::time(&rawtime);
		std::tm time_tm;
		localtime_r(&rawtime, &time_tm);

		strftime(name_buffer, 80, "/home/nvidia/tmp/Cooperative Driving/vehicle_log__%F_%H%M%S.csv", &time_tm);
		log_file_ = fopen(name_buffer, "w");
		if (log_file_ == nullptr) {
			std::cout << "Fail to open file: " << name_buffer << std::endl;
		}
		if (log_file_ != nullptr) {
			fprintf(log_file_, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\r\n",
					"time",
					"x",
					"y",
                    "theta",
                    "speed",
                    "steer_angle",
                    "front_steering_angle",
                    "index",
                    "lateral_error",
                    "heading_error",
                    "torque",
					"ref_heading");
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
	/*
	* param
	@steering_wheel_angle: -500 deg turn right ~ 500 deg turn left
	*/
	if (steering_wheel_angle < -500 || steering_wheel_angle > 500) {
		std::cout << "# VALUE EXCEED #  steering wheel angle exceed range [-500, 500]" << std::endl;
	}
    // steering_wheel_angle > 0 means turning left
    SteeringControl steering_control;
    steering_control.SC_SteeringControlRequest = 2;
    //SteeringAngle in -500~500 deg
    steering_control.SC_TargetSteeringAngle = -1.0 * steering_wheel_angle;
    //SteeringSpeed in 200-400 deg/s
    steering_control.SC_TargetSteeringSpeed = 400.0; // ??? 200
    steering_control.SC_SetHandTorqueLimitValid = 1;
   
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT;
    SendSteerControl(steering_control);
}

void ControlSender::ControlSteerTorque(const double steering_wheel_torque) {
	/*
	* param
	@steering_wheel_torque: 2Nm ~ 5Nm
	*/
    // steering_wheel_torque > 0 means turning left
    SteeringControl steering_control;
    steering_control.SC_SteeringControlRequest = 1;
    //torque in 2-5 Nm
    steering_control.SC_TargetTorque = std::fabs(steering_wheel_torque);
	if (steering_control.SC_TargetTorque > 5 || steering_control.SC_TargetTorque < -2) {
		std::cout << "# VALUE EXCEED #  steering wheel torque exceed range [2, 5]" << std::endl;
	}
    steering_control.SC_TargetTorqueSign = steering_wheel_torque < 0 ? 1 : 0;
    steering_control.SC_SetHandTorqueLimitValid = 1;
    steering_control.SC_SetHandTorqueLimit = HANDTORQUE_LIMIT; 
    SendSteerControl(steering_control);
}


void ControlSender::ControlAccel(const double accel_command) {
	/*
	* param
	@accel_command: ???
	*/
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


// cannot check
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


// cannot check
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


// unknown
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
        usleep(20000); // 20ms
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
        rw_lock_.lock(); // ???
        if(!(vehicle_info_.FLAG_SERIAL && vehicle_info_.FLAG_CAN)){ 
            ROS_INFO("hasn't receive vehicle info");
            rw_lock_.unlock(); // ???
            usleep(20000);
            continue;
        }
        //send a fixed angle 
        /* 
            const double steering_angle_command = -100.0;
            ControlSteerAngle(steering_angle_command);
        */

        //send a fixed torque 
        /*
            const double torque_command = 3;
            ControlSteerTorque(torque_command);
        */

        // lon_controller 
		// cannot check
        const double accel_command = lon_controller.ComputeAccel(vehicle_info_.speed/3.6, CONTROL_T);
        ControlAccel(accel_command);
        //lat_controller use torque
        
        const double steer_torque_command = lat_controller.ComputeSteerTorque(
            vehicle_info_.x, vehicle_info_.y, vehicle_info_.theta, vehicle_info_.steer_angle);
        ControlSteerTorque(steer_torque_command);
        
        //lat_controller use angle
        /*
        const double steer_angle_command = lat_controller.ComputeSteerAngle(
            vehicle_info_.x, vehicle_info_.y, vehicle_info_.theta, vehicle_info_.steer_angle);
        ROS_INFO("current steerangle is %lf",steer_angle_command);
        ControlSteerAngle(-1 * steer_angle_command);
        */
		// unsafe ??
		index_ = lat_controller.get_path_point_index(); // ??
        lat_log_ = lat_controller.get_lateral_error();
        head_log_ = lat_controller.get_heading_error();
	    torque = lat_controller.get_torque(); // ??
	    ref_heading = lat_controller.get_ref_heading(); // ??
        rw_lock_.unlock(); // ??
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
   
    /*
	* param:
	*/

	// unsafe need set
	if (msg->VI_VehicleSpeed < 0 || msg->VI_VehicleSpeed > 30) {
		std::cerr << "# VALUE EXCEED #  vehicle speed exceed [0, 30]" << std::endl;
	}
    vehicle_info_.speed = msg->VI_VehicleSpeed;

	if (msg->SR_CurrentSteeringAngle < -500 || msg->SR_CurrentSteeringAngle > 500) {
		std::cerr << "# VALUE EXCEED #  steer angle exceed [-500, 500]" << std::endl;
	}
    vehicle_info_.steer_angle = msg->SR_CurrentSteeringAngle;

	if (msg->VI_FrontSteeringAngle < -500 || msg->VI_FrontSteeringAngle > 500) {
		std::cerr << "# VALUE EXCEED #  front steering angle exceed [-500, 500]" << std::endl;
	}
    vehicle_info_.front_steering_angle = msg->VI_FrontSteeringAngle;

    vehicle_info_.FLAG_CAN = 1;
  
}

void ControlSender::SerialReceive(const localization::gps::ConstPtr& msg){
   
	if (msg->x < -500 || msg->x > 500) { ////####
		std::cerr << "# VALUE EXCEED #  x exceed [-500, 500]" << std::endl;
	}
    vehicle_info_.x = msg->x;
	if (msg->y < -500 || msg->y > 500) { ////####
		std::cerr << "# VALUE EXCEED #  y exceed [-500, 500]" << std::endl;
	}
    vehicle_info_.y = msg->y;
	if (stod(msg->Heading) < 0 || stod(msg->Heading) > 360) {
		std::cerr << "# VALUE EXCEED #  stod(msg->Heading) exceed [0, 360]" << std::endl;
	}
    vehicle_info_.theta = stod(msg->Heading);

    vehicle_info_.FLAG_SERIAL = 1;
  
}

void ControlSender::StartReceive(){
    subCan_ = n_.subscribe("CAN_INFO", 1, &ControlSender::CANReceive, this); // 1000
    subSerial_ = n_.subscribe("GPS_INFO", 1, &ControlSender::SerialReceive, this); // 1000
    ros::Rate loop_rate(RECEIVE_HZ);
    while(ros::ok())
    {
        rw_lock_.lock();
        //frame++;
        //ROS_INFO("this is %d frame",frame);
        ros::spinOnce();
	    if(vehicle_info_.FLAG_CAN == 1 && vehicle_info_.FLAG_SERIAL == 1){
        	long now_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		    double now_in_seconds = static_cast<double> (now_in_nanoseconds * 1e-9);

			double nor_theta = NormalizeAngle(M_PI_2 - vehicle_info_.theta / 180.0 * M_PI);

			if (nor_theta < 0 || nor_theta > 2 * M_PI) {
				std::cerr << "# VALUE EXCEED #  nor theta exceed range [0, 2pi]" << std::endl;
			}

			// east-north-sky coordinate system x-y-z
            if(ENABLE_LOG && log_file_ != nullptr){
                fprintf(log_file_,"%.6f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%.2f,%.2f,%.2f,%.2f\r\n",
                now_in_seconds, 
				vehicle_info_.x,
				vehicle_info_.y,
                nor_theta,
                vehicle_info_.speed,
                vehicle_info_.steer_angle,
                vehicle_info_.front_steering_angle,
                index_,
                lat_log_,
                head_log_,
		        torque,
		        ref_heading);
            }
        }
        rw_lock_.unlock(); // ??
        loop_rate_.sleep();
    }
}


