#include "canbus_reader.hpp"
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <cmath>
#include <cstring>

#include <string>
#include <iostream>
#include <mutex>
#include "canbus/frame.h"
#include <thread>
#define HSEVHU_SR_ID 0x50A // 100Hz
#define HSEVCO_CR_ID 0x58C // 100Hz
#define HSEVCO_CBW_ID 0x5C0 // 50Hz
#define HSEVCO_SI2_ID 0x68A // 100Hz
#define HSEVCO_SI1_ID 0x68B // 100Hz
#define HSEVCO_VI_ID 0x68F // 100Hz
#define HSEVCO_WSI_ID 0x68D // 100Hz



bool CanBusReader::InitSocket() {
	// Create a socket file descriptor
	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
		perror("Socket error");
		return false;
	}
	// cout << "Receiver's linux file descriptor is " << s << endl;
    // Copy C string to ifr (network device)
	// Standard ioctls of network device 
    ifreq ifr;
	strcpy(ifr.ifr_name, "can0");
	//system call manipulates the underlying device parameters of special files             
	ioctl(s, SIOCGIFINDEX, &ifr);
	sockaddr_can addr;
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
    // Bind socketaddr and file describe symbol
	if (bind(s, (sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind error");
		return false;
	}
	s_ = s;
	return true;
}

<<<<<<< HEAD
bool CanBusReader::ReadCanBus() {
=======
bool CanBusReader::ReadCanBus(SteeringReport* const steering_report,
                             ChassisReport* const chassis_report) {
>>>>>>> 148e6f13f4a6414c360c38418abb1ae10e8aed2b
	using namespace std;

	can_frame frame;

	int nbytes = read(s_, &frame, sizeof(can_frame));
	if (nbytes < 0) {
		perror("Read error");
		return false;
	}
<<<<<<< HEAD
	if(!DataCheck(frame))
	{
		cout << "this is a error frame" << endl;
=======
	if(!DataCheck(frame)) {
		cout << "This is an error frame" << endl;
>>>>>>> 148e6f13f4a6414c360c38418abb1ae10e8aed2b
		return false;
	}
	rw_mutex.lock();
	switch(frame.can_id) {
		case HSEVHU_SR_ID: {
			cout << "Received HSEVHU_SR message." << endl;
			// steering wheel angle
			steering_report.SR_CurrentSteeringAngle =
			    ((((int)frame.data[2] << 8) + frame.data[1]) & ((1 << 14) - 1)) * 0.1 - 600.0;				
			// cout << hex << CSA << endl;
			// steering wheel speed
			steering_report.SR_CurrentSteeringSpeed =
				(((int)frame.data[3] << 2) + (frame.data[2] >> 6)) & ((1 << 10) - 1);
			// steering wheel hand torque
		    steering_report.SR_HandTorque =
			    ((((int)frame.data[5] << 8) + frame.data[4]) & ((1 << 10) - 1)) * 0.01;
			// steering wheel hand torque sign
			steering_report.SR_HandTorqueSign = (int)((frame.data[5] >> 2) & 1);
			// work mode
			steering_report.SR_WorkMode = (int)((frame.data[5] >> 3) & ((1 << 3) - 1));
			// steering wheel hand torque limit
			steering_report.SR_HandTorqueLimit =
			    ((((int)frame.data[6] << 2) + (frame.data[5] >> 6)) & ((1 << 10) - 1)) * 0.01;
			// steering report error
			steering_report.SR_Error = frame.data[7] & 3;
			// steering report waring
			steering_report.SR_Warning = ((frame.data[7] >> 2) & 3);
			//liveCounter
			steering_report.SR_LiveCounter = (frame.data[7] >> 4) & ((1 << 4) - 1);
			PrintCanFrameDLC(frame);
			PrintSteeringReport();
			break;
		}
		case HSEVCO_VI_ID: {
			cout << "Received HSEVCO_VI message" << endl;
			// TODO: do we need (int) or (double)?
			// gear info
			chassis_report.VI_GearInfo = frame.data[0] & ((1 << 3) - 1);
			// brake info
			chassis_report.VI_BrakeInfo = ((frame.data[0] >> 3 ) & 1 );
			// button 1
			chassis_report.VI_Button1 = (frame.data[0] >> 4 ) & 1;
			// button 2
			chassis_report.VI_Button2 = (frame.data[0] >> 5 ) & 1;
			// hand brake
			chassis_report.VI_HandBrakeSt = (frame.data[0] >> 6) & 1;
			// jerk st
			chassis_report.VI_JerkSt = (frame.data[0] >> 7) & 1;
			// accel pedal position
			chassis_report.VI_AccelPedalPosition = (frame.data[1] & ((1 << 8) - 1)) * 0.4;
            // front steering angle
			chassis_report.VI_FrontSteeringAngle =
				((((int)frame.data[3] << 8) + frame.data[2]) & ((1 << 16) - 1)) * 0.1 - 600.0;
			// ramaining times
			chassis_report.VI_RemainingTimes =
				(((int)frame.data[5] << 8) + frame.data[4]) & ((1 << 12) - 1);
			// vehicle speed
			chassis_report.VI_VehicleSpeed = 
				((((int)frame.data[7] << 8) + frame.data[6]) & ((1 << 16) - 1)) * 0.01;
			PrintCanFrameDLC(frame);
			PrintVehicleInfo();
			break;
		}
		case HSEVCO_SI2_ID:{
			cout << "Received HSEVCO_SI2 message" << endl;
			// lon accel
			chassis_report.SI2_LongitudinalAccel =
				((((int)frame.data[1] << 8) + frame.data[0]) & ((1 << 12) - 1)) * 0.01 - 20;
			// lat accel
			chassis_report.SI2_LateralAccel =
				((((int)frame.data[2] << 4) + (frame.data[1] >> 4) & ((1 << 12) - 1)) * 0.01 - 20);
			// yawrate
			chassis_report.SI2_YawRate =
				((((int)frame.data[4] << 8) + frame.data[3]) & ((1 << 12) - 1)) * 0.05 - 100;
			PrintCanFrameDLC(frame);
			PrintSInfo2();
			break;
		}
	}
<<<<<<< HEAD
	rw_mutex.unlock();


=======
>>>>>>> 148e6f13f4a6414c360c38418abb1ae10e8aed2b
	return true;
}

bool CanBusReader::CloseSocket() {
	if (close(s_) < 0) {
		perror("Close error");
		return false;
	}
	return true;
}

void CanBusReader::PrintCanFrameDLC(const can_frame& frame) {
	for (int i = 0; i < frame.can_dlc; ++i) {
		std::cout << std::hex << (int)frame.data[i] << " ";
	}
	std::cout << std::endl;
}

void CanBusReader::PrintSteeringReport() {
	using namespace std;

	// steering wheel angle
	cout << "Steering wheel angle: " << steering_report.SR_CurrentSteeringAngle << " deg" << endl;
	// steering wheel angle speed
	cout << "Steering wheel angle speed: " << steering_report.SR_CurrentSteeringSpeed << " deg/s" << endl;
	// hand torque
	cout << "Hand torque: " << steering_report.SR_HandTorque << " Nm" << endl;
    // hand torque sign
	const string hand_torque_sign = steering_report.SR_HandTorqueSign == 0 ? "left" : "right";
	cout << "Hand torque sign: " << hand_torque_sign << endl;
	// hand torque limit
	cout << "Hand torque limit " << steering_report.SR_HandTorqueLimit << " Nm" << endl;
    // work mode
	string work_mode;
	switch (steering_report.SR_WorkMode){
		case 0:
			work_mode = "Manual";
			break;
		case 1:
			work_mode = "Angle";
			break;
		case 2:
			work_mode = "Torque";
			break;
		case 7:
			work_mode = "Error";
			break;
		default:
			work_mode = "Unknown";
			break;
	}
	cout << "Workmode: " << work_mode << endl;
    // error
	string error;
	switch (steering_report.SR_Error){
		case 0:
			error = "NoError";
			break;
		case 1:
			error = "OverCurrent";
			break;
		case 2:
			error = "LoseSAS";
			break;
		default:
			error = "Unknown";
			break;
	}
	cout << "Error: " << error << endl;
	// warning
	string warning;
	switch (steering_report.SR_Warning){
		case 0:
			warning = "None";
			break;
		case 1:
			warning = "Left Limit";
			break;
		case 2:
			warning = "Right Limit";
			break;
		default:
			warning = "Unknown";
			break;
	}
	cout << "Warning: " << warning << endl;
	// live counter
	cout << "LiveCounter: " << steering_report.SR_LiveCounter << endl;
}
void CanBusReader::PrintVehicleInfo() {
	using namespace std;

	// gear info
	switch (chassis_report.VI_GearInfo){
		case 0:
			cout << "Gear: P" << endl;
			break;
		case 1:
			cout << "Gear: R" << endl;
			break;
		case 2:
			cout << "Gear: N" << endl;
			break;
		case 3:
			cout << "Gear: D" << endl;
			break;
		default:
			cout << "Gear: Unknown" << endl;
			break;
	}
	// brake info
	switch (chassis_report.VI_BrakeInfo){
		case 0:
			cout << "Brake: No Brake" << endl;
			break;
		case 1:
			cout << "Brake: Brake" << endl;
			break;
		default:
			cout << "Brake: Unknown" << endl;
			break;
	}
	// button 1
	switch (chassis_report.VI_Button1){
		case 0:
			cout << "Button 1: No Press" << endl;
			break;
		case 1:
			cout << "Button 1: Pressed" << endl;
			break;
		default:
			cout << "Button 1: Unknown" << endl;
			break;
	}
	// button 2
	switch (chassis_report.VI_Button2){
		case 0:
			cout << "Button 2: No Press" << endl;
			break;
		case 1:
			cout << "Button 2: Pressed" << endl;
			break;
		default:
			cout << "Button 2: Unknown" << endl;
			break;
	}
    // handbrake
	switch (chassis_report.VI_HandBrakeSt){
		case 0:
			cout << "Hand Brake: No Brake" << endl;
			break;
		case 1:
			cout << "Hand Brake: Brake" << endl;
			break;
		default:
			cout << "Hand Brake: Unknown" << endl;
			break;
	}
    // jerk st
	switch (chassis_report.VI_JerkSt){
		case 0:
			cout << "JerkSt: No Press" << endl;
			break;
		case 1:
			cout << "JerkSt: Pressed" << endl;
			break;
		default:
			cout << "JerkSt: Unknown" << endl;
			break;
	}
	// accel pedal position
	cout << "Accel pedal position: " << chassis_report.VI_AccelPedalPosition << " % " << endl;
    // front steering angle
	cout << "Front steering angle: " << chassis_report.VI_FrontSteeringAngle << " deg " << endl;
	// remaining times
	cout << "Remaining times: " << chassis_report.VI_RemainingTimes << " s" << endl;
	// vehicle speed
	cout << "Vehicle speed: " << chassis_report.VI_VehicleSpeed << " km/h" << endl;
}

void CanBusReader::PrintSInfo2() {
	std::cout << "Longitudinal accel: " << chassis_report.SI2_LongitudinalAccel << " m/s2 " << std::endl;
	std::cout << "Lateral accel: " << chassis_report.SI2_LateralAccel << " m/s2 " << std::endl;
	std::cout << "Yawrate is " << chassis_report.SI2_YawRate << " deg/s " << std::endl;
}




bool CanBusReader::DataCheck(const can_frame& frame){
	uint8_t CheckSum = frame.data[0];
<<<<<<< HEAD
	for(int i = 1; i < frame.can_dlc; ++i){
=======
	for(int i = 1; i < frame.can_dlc; ++i) {
>>>>>>> 148e6f13f4a6414c360c38418abb1ae10e8aed2b
		CheckSum ^= frame.data[i];
	}
	return CheckSum == 0;
}

void CanBusReader::PublishToRos(){
	std::cout << "start publish thread id is" << std::this_thread::get_id() <<std::endl;
	ros::Publisher pub_to_CANINFO = this->n.advertise<canbus::frame>("CAN_INFO",1000);
	canbus::frame msg;

	while(ros::ok()){
		rw_mutex.lock();

		//chassis_report
		msg.VI_GearInfo = chassis_report.VI_GearInfo;
		msg.VI_BrakeInfo = chassis_report.VI_BrakeInfo;
		msg.VI_Button1 = chassis_report.VI_Button1;
		msg.VI_Button2 = chassis_report.VI_Button2;
		msg.VI_HandBrakeSt = chassis_report.VI_HandBrakeSt;
		msg.VI_JerkSt = chassis_report.VI_JerkSt;
		msg.VI_AccelPedalPosition = chassis_report.VI_AccelPedalPosition;
		msg.VI_FrontSteeringAngle = chassis_report.VI_FrontSteeringAngle;
		msg.VI_RemainingTimes = chassis_report.VI_RemainingTimes;
		msg.VI_VehicleSpeed = chassis_report.VI_VehicleSpeed;
		msg.SI2_LongitudinalAccel = chassis_report.SI2_LongitudinalAccel;
		msg.SI2_LateralAccel = chassis_report.SI2_LateralAccel;
		msg.SI2_YawRate = chassis_report.SI2_YawRate;

		//steering_report
		msg.SR_CurrentSteeringAngle = steering_report.SR_CurrentSteeringAngle;
		msg.SR_CurrentSteeringSpeed = steering_report.SR_CurrentSteeringSpeed;
		msg.SR_HandTorque = steering_report.SR_HandTorque;
		msg.SR_HandTorqueSign =  steering_report.SR_HandTorqueSign;
		msg.SR_WorkMode = steering_report.SR_WorkMode;
		msg.SR_HandTorqueLimit = steering_report.SR_HandTorqueLimit;
		msg.SR_Error = steering_report.SR_Error;
		msg.SR_Warning = steering_report.SR_Warning;
		msg.SR_LiveCounter = steering_report.SR_LiveCounter;

		pub_to_CANINFO.publish(msg);
		rw_mutex.unlock();
		ros::Rate loop_rate(SEND_HZ);
	}

}

void CanBusReader::StartRead(){
	using namespace std;
	std::cout << "start receive thread id is" << std::this_thread::get_id() << endl;
	if (!InitSocket()) {
        cout << "Init socket failed" << endl;
        return ;
    } else {
        cout << "Init socket success" << endl;
    }
	while (ros::ok()) {
        const auto start_t = chrono::system_clock::now();

		if (!ReadCanBus()) {
			cout << "Read canbus failed!" << endl;
		}
        const auto end_t = chrono::system_clock::now();
        const auto elapsed_t = chrono::duration<double>(end_t - start_t);
        if (elapsed_t.count() < CANBUS_T) {
            const auto remaining_t = chrono::duration<double>(CANBUS_T) - elapsed_t;
            // cout << "Canbus thread sleeps for " << remaining_t.count() << " seconds." << endl;
            this_thread::sleep_for(remaining_t);
        } else {
            cout << "Warning: canbus loop spent " << elapsed_t.count() << " seconds larger than " 
                 << CANBUS_T << " seconds. " << endl;
        }
    }

    if (!CloseSocket()) {
        cout << "Close socket failed" << endl;
    } else {
        cout << "Close socket succuss" << endl;
    }
}