// TODO: check if there is any unnecessary header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <iostream>
#include <string>

int main(int argc, char **argv){
	using namespace std;

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
	frame.data[1] = 0x82;
	frame.data[2] = 0x25;
	frame.data[3] = 0x32;

	//send a can_frame to socket and linux kernel help us to communication with CAN bus
	write(s, &frame, sizeof(struct can_frame));

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
