#include "canStruct.hpp"

using namespace std;


int main(int argc, char **argv){


	cout << "CAN Sockets Demo" << endl;

	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	ifreq ifr;
	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	sockaddr_can addr;
	memset(&addr, 0, sizeof(addr));

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	/*
		*** When create a CAN frame we neet to set its memory to 0 use memset() *** 
	
	*/
	can_frame frame;
	memset(frame.data, 0, sizeof(frame.data));
  
	frame.can_id = 0x501;
	frame.can_dlc = 8;

	//set SteeringControlRequest to angle
	//set steer angle to 0

	/*
		data[1] low bit is request
		data[1] high bit is  steering angle's low bit
		data[2] is steering angle's high bit
		data[3]*2 is target steering speed
	*/

	/*
		SteeringContolRequest -> data[1]'s low 4 bit 
		SteeringAngle -> data[2] data[1]'s high 4 bit - 600
		TargetSteeringSpeed -> data[3] * 2
		TargetTorque -> data[5]'s low 2 bit data[4]  * 0.01
		TargetTorqueSign -> data[5]'s low 4 bit
		TorqueLimitVaild data[5]'s  high 4 bit
		handTorqueLimit data[6]  data[5]'s high 2 bit 
	*/
	frame.data[1] = 0x82;
	frame.data[2] = 0x25; //600 's hex is 258 

	frame.data[3] = 0x32; //50 

	/*
	frame.data[1] = 0x01;
	frame.data[4] = 0b00101100;       0x2C  if turn left target torque is 0x12C else is 0x52C
	frame.data[5] = 0b00100001;       0x21	target is 0
	frame.data[6] = 0b01111101;		  0x7D	
	*/
	
	


	//send a can_frame to socket and linux kernel help us to communication with CAN bus
	write(s, &frame, sizeof(struct can_frame));

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
