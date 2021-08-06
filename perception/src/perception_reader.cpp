#include "perception_reader.hpp"
#include <chrono>
#include <stdlib.h>

#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdio.h>
#include <cmath>
#include <cstring>

#include <string>
#include <iostream>
#include <mutex>
#include <thread>

#include "perception/frame.h"

#define HSEVHU_SR_ID 0x50A // 100Hz 
#define HSEVCO_CR_ID 0x58C // 100Hz
#define HSEVCO_CBW_ID 0x5C0 // 50Hz
#define HSEVCO_SI2_ID 0x68A // 100Hz
#define HSEVCO_SI1_ID 0x68B // 100Hz
#define HSEVCO_VI_ID 0x68F // 100Hz
#define HSEVCO_WSI_ID 0x68D // 100Hz
#define ENABLE_CANBUS_LOG 0


#define RT1A_DIS 0x760
#define RT1B_DIS 0x761
#define RTS1A_DIS 0x740

Perception::Perception() {
	n_.param("can_port_num",can_port_,std::string("can0"));
	//n_.param("enable_log",can_port_,std::string("can0"));
	//n_.param("can_port_num",can_port_,std::string("can0"));
	/*
	if (ENABLE_CANBUS_LOG) {
		time_t rawtime;
		char name_buffer[80];
		std::time(&rawtime);
		std::tm time_tm;
		localtime_r(&rawtime, &time_tm);
		strftime(name_buffer, 80, "/home/nvidia/tmp/canbus_log__%F_%H%M%S.csv", &time_tm);
		log_file_ = fopen(name_buffer, "w");
		if (log_file_ == nullptr) {
			std::cout << "Fail to open file:" << name_buffer << std::endl;
		}
		if (log_file_ != nullptr) {
			fprintf(log_file_, "%s %s %s %s %s %s %s %s %s %s %s %s \r\n",
					"time",
					"steering_angle",
					"steering_speed",
					"hand_torque",
					"workmode",
					"hand_torque_limit",
					"accel_pedal_position",
					"front_steering_angle",
					"speed",
					"lon_accel",
					"lat_accel",
					"yaw_rate");
			fflush(log_file_);
		}
	}
	*/
}

Perception::~Perception() {
	if (ENABLE_CANBUS_LOG) {
		if (log_file_ != nullptr) {
		fclose(log_file_);
		log_file_ = nullptr;
		}
	}
}

bool Perception::InitSocket() {
	// Create a socket file descriptor
	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
		perror("Socket error");
		return false;
	}
    // Copy C string to ifr (network device)
	// Standard ioctls of network device 
    ifreq ifr;
	strcpy(ifr.ifr_name, can_port_.c_str());
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
	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
	
	return true;
}


bool Perception::ReadCanBus() {
	using namespace std;
	can_frame frame;
	int nbytes = read(s_, &frame, sizeof(can_frame));
	if (nbytes < 0) {
		perror("Read error");
		return false;
	}
/*
	if(!DataCheck(frame)) {
		cout << "This is an error frame" << endl;
		return false;
	}
*/
    //cout <<hex<< frame.can_id << endl;
	rw_mutex_.lock();
	//bitset<64> bit_array;
	//ConvertData2BitSet(frame,bit_array);
	switch(frame.can_id) {
		case RT1A_DIS: {
			move_target_.lat_v =  (((int)frame.data[5] << 4) + (frame.data[4] >> 4)) * 0.025 - 20;	
			move_target_.long_dis =  ((((int)frame.data[1] << 8) + frame.data[0]) & ((1 << 12) - 1)) * 0.1;	
			move_target_.lat_dis = ((((int)frame.data[4] << 8) + frame.data[3]) & ((1 << 12) - 1)) * 0.1 - 50;	
			move_target_.long_v = (((int)frame.data[2] << 4) + (frame.data[1] >> 4)) * 0.05 - 100;	
			break;
		}
		case RT1B_DIS: {
			
			break;
		}
		case RTS1A_DIS: {
			//station_target_.long_dis = (bitset<11>(bit_array.to_string().substr(bit_array.size() - 12,12))).to_ulong();
			//station_target_.long_dis = (bitset<11>(bit_array.to_string().substr(bit_array.size() - 24,12))).to_ulong();
			station_target_.long_dis = ((((int)frame.data[1] << 8) + frame.data[0]) & ((1 << 12) - 1)) * 0.1;	
			station_target_.lat_dis = (((int)frame.data[2] << 4) + (frame.data[1] >> 4)) * 0.1 - 50;	
			//station_target_.long_v = (((int)frame.data[2] << 4) + (frame.data[1] >> 4)) * 0.1 - 50;	
			//station_target_.lat_v = (((int)frame.data[2] << 4) + (frame.data[1] >> 4)) * 0.1 - 50;	
			break;
		}
	}
	rw_mutex_.unlock();//lock pass
	return true;
}

bool Perception::CloseSocket() {
	if (close(s_) < 0) {
		perror("Close error");
		return false;
	}
	return true;
}


/*
bool Perception::DataCheck(const can_frame& frame) {
	uint8_t CheckSum = frame.data[0];
	for(int i = 1; i < frame.can_dlc; ++i) {
		CheckSum ^= frame.data[i];
	}
	return CheckSum == 0;
}
*/
void Perception::PublishToRos() {
	ros::Rate loop_rate_(SEND_HZ);
	std::cout << "start publish thread id is" << std::this_thread::get_id() <<std::endl;
	ros::Publisher pub_to_CANINFO = this->n_.advertise<perception::frame>("PERCEPTION_INFO",10);
	

	while(ros::ok()) {
		rw_mutex_.lock();
		perception::frame msg;
		perception::object_frame obj_frame;
		perception::object_frame_station obj_frame_station;
		obj_frame_station.long_dis = station_target_.long_dis;
		obj_frame_station.lat_dis = station_target_.lat_dis;
		obj_frame.long_v = move_target_.long_v;
		obj_frame.lat_v = move_target_.lat_v;
		obj_frame.long_dis = move_target_.long_dis;
		obj_frame.lat_dis = move_target_.lat_dis;
		msg.station_objs.push_back(obj_frame_station);
		msg.objs.push_back(obj_frame);

		pub_to_CANINFO.publish(msg);
		rw_mutex_.unlock();
		loop_rate_.sleep();
	}
}

void Perception::StartRead() {
	using namespace std;
	std::cout << "start receive thread id is" << std::this_thread::get_id() << std::endl;
	ros::Rate loop_rate(READ_HZ);
	if (!InitSocket()) {
        cout << "Init socket failed" << endl;
        return ;
    } else {
        cout << "Init socket success" << endl;
    }
	while (ros::ok()) {
		if (!ReadCanBus()) {
			cout << "Read canbus failed!" << endl;
		}
     		loop_rate.sleep();
    }
    if (!CloseSocket()) {
        cout << "Close socket failed" << endl;
    } else {
        cout << "Close socket succuss" << endl;
    }
}



void Perception::PrintCanFrameDLC(const can_frame& frame) {
	for(int i = 0; i < frame.can_dlc; ++i) {
		std::cout << std::hex << (int)frame.data[i] << " ";
	}
	std::cout << std::endl;
}
/*
void Perception::ConvertData2BitSet(const can_frame& frame,bitset<64> &bit_array) {
	string tmp;
	for(int i = 0; i < 8; i++) {
		bitset<8> tmp_set(frame.data[i]);
		tmp += tmp_set.to_string();
	}
	bit_array = bitset<64>(tmp);
	return;
}
*/