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
        frame->data[1] = 0; 
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



bool ControlSender::StartWrite(){
    using namespace std;
    if (!InitSocket()) {
        cout << "Init socket failed" << endl;
        return false;
    } else {
        cout << "Init socket success" << endl;
    }
    while (ros::ok) {
        const auto start_t = chrono::system_clock::now();
        rw_lock_.lock();
        const double steering_angle_command = -10.0;
        ControlSteerAngle(steering_angle_command);
        const double accel_command = 0.5;
        ControlAccel(accel_command);
        rw_lock_.unlock();
        const auto end_t = chrono::system_clock::now();
        const auto elapsed_t = chrono::duration<double>(end_t - start_t);
        if (elapsed_t.count() < CONTROL_T) {
            const auto remaining_t = chrono::duration<double>(CONTROL_T) - elapsed_t;
            // cout << "Control thread sleeps for " << remaining_t.count() << " seconds." << endl;
            this_thread::sleep_for(remaining_t);
        } else {
            cout << "Warning: control loop spent " << elapsed_t.count() << " seconds larger than " 
                 << CONTROL_T << " seconds. " << endl;
        }
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
    ROS_INFO("I heard VI_GearInfo [%d]",msg->VI_GearInfo);
    ROS_INFO("I heard VI_BrakeInfo [%d]",msg->VI_BrakeInfo);
    ROS_INFO("I heard VI_Button1 [%d]",msg->VI_Button1);
    ROS_INFO("I heard VI_Button2 [%d]",msg->VI_Button2);
    ROS_INFO("I heard VI_HandBrakeSt [%d]",msg->VI_HandBrakeSt);
    ROS_INFO("I heard VI_JerkSt [%d]",msg->VI_JerkSt);
    ROS_INFO("I heard VI_AccelPedalPosition [%f]",msg->VI_AccelPedalPosition);
    ROS_INFO("I heard VI_FrontSteeringAngle [%f]",msg->VI_FrontSteeringAngle);
    ROS_INFO("I heard VI_RemainingTimes [%f]",msg->VI_RemainingTimes);
    ROS_INFO("I heard VI_VehicleSpeed [%f]",msg->VI_VehicleSpeed);
    ROS_INFO("I heard SI2_LongitudinalAccel [%f]",msg->SI2_LongitudinalAccel);
    ROS_INFO("I heard SI2_LateralAccel [%f]",msg->SI2_LateralAccel);
    ROS_INFO("I heard SI2_YawRate [%f]",msg->SI2_YawRate);


    ROS_INFO("I heard SR_CurrentSteeringAngle [%f]",msg->SR_CurrentSteeringAngle);
    ROS_INFO("I heard SR_CurrentSteeringSpeed [%f]",msg->SR_CurrentSteeringSpeed);
    ROS_INFO("I heard SR_HandTorque [%f]",msg->SR_HandTorque);
    ROS_INFO("I heard SR_HandTorqueSign [%f]",msg->SR_HandTorqueSign);
    ROS_INFO("I heard SR_WorkMode [%f]",msg->SR_WorkMode);
    ROS_INFO("I heard SR_HandTorqueLimit [%f]",msg->SR_HandTorqueLimit);
    ROS_INFO("I heard SR_Error [%f]",msg->SR_Error);
    ROS_INFO("I heard SR_Warning [%f]",msg->SR_Warning);
    ROS_INFO("I heard SR_LiveCounter [%f]",msg->SR_LiveCounter);
}


void ControlSender::SerialReceive(const localization::gps::ConstPtr& msg){
    ROS_INFO("I heard FPD_Header [%s]",msg->FPD_Header.c_str());
    ROS_INFO("I heard FPD_GPSWeek [%s]",msg->FPD_GPSWeek.c_str());
    ROS_INFO("I heard FPD_GPSTime [%s]",msg->FPD_GPSTime.c_str());
    ROS_INFO("I heard Heading [%s]",msg->Heading.c_str());
    ROS_INFO("I heard Pitch [%s]",msg->Pitch.c_str());
    ROS_INFO("I heard Roll [%s]",msg->Roll.c_str());
    ROS_INFO("I heard Lattitude [%s]",msg->Lattitude.c_str());
    ROS_INFO("I heard Longitude [%s]",msg->Longitude.c_str());
    ROS_INFO("I heard Altitude [%s]",msg->Altitude.c_str());
    ROS_INFO("I heard Ve [%s]",msg->Ve.c_str());
    ROS_INFO("I heard Vn [%s]",msg->Vn.c_str());
    ROS_INFO("I heard Vu [%s]",msg->Vu.c_str());
    ROS_INFO("I heard Baseline [%s]",msg->Baseline.c_str());
    ROS_INFO("I heard NSV1 [%s]",msg->NSV1.c_str());
    ROS_INFO("I heard NSV2 [%s]",msg->NSV2.c_str());
    ROS_INFO("I heard Status [%s]",msg->Status.c_str());
    ROS_INFO("I heard FPD_Cs [%s]",msg->FPD_Cs.c_str());
    ROS_INFO("I heard FPD_CrLf [%s]",msg->FPD_CrLf.c_str());


    ROS_INFO("I heard IMU_Header [%s]",msg->IMU_Header.c_str());
    ROS_INFO("I heard IMU_GPSWeek [%s]",msg->IMU_GPSWeek.c_str());
    ROS_INFO("I heard IMU_GPSTime [%s]",msg->IMU_GPSTime.c_str());
    ROS_INFO("I heard GyroX [%s]",msg->GyroX.c_str());
    ROS_INFO("I heard GyroY [%s]",msg->GyroY.c_str());
    ROS_INFO("I heard GyroZ [%s]",msg->GyroZ.c_str());
    ROS_INFO("I heard AccX [%s]",msg->AccX.c_str());
    ROS_INFO("I heard AccY [%s]",msg->AccY.c_str());
    ROS_INFO("I heard AccZ [%s]",msg->AccZ.c_str());
    ROS_INFO("I heard Tpr [%s]",msg->Tpr.c_str());
    ROS_INFO("I heard IMU_Cs [%s]",msg->IMU_Cs.c_str());
    ROS_INFO("I heard IMU_CrLf [%s]",msg->IMU_CrLf.c_str());
}



void ControlSender::StartReceive(){
    int frame = 0;
    subCan_ = n_.subscribe("CAN_INFO",1000,&ControlSender::CANReceive,this);
    subSerial_ = n_.subscribe("GPS_INFO",1000,&ControlSender::SerialReceive,this);
    while(ros::ok())
    {
        rw_lock_.lock();
        frame++;
        ROS_INFO("this is [%d] frame",frame);
        ros::spinOnce();
        rw_lock_.unlock();
        loop_rate_.sleep();
    }
}