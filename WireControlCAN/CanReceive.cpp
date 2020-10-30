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

#include <bitset>
#include <string>
#include <iostream>

#include "canStruct.hpp"
#include <math.h>
//sudo ip link add dev vcan0 type vcan 
//sudo ifconfig vcan0 up

int main(int argc, char **argv) {
	using namespace std;

	cout << "CAN Sockets Receive Demo." << endl;

	// create a socket file describe symbol
	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
		perror("Socket");
		return 1;
	}
	cout << "Receiver's linux file descriptor is " << s << endl;

    //copy c string to ifr
    ifreq ifr;
	strcpy(ifr.ifr_name, "can0");               
	ioctl(s, SIOCGIFINDEX, &ifr); 

	/*
	    define a system call by user 
	    input-output control
    */
	sockaddr_can addr;
	
	memset(&addr, 0, sizeof(addr));

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    //bind socketaddr and file describe symbol
	if (bind(s, (sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	SteeringReport sr;
	//int frameNum = 0;
	int nbytes = 0;
	can_frame frame;
	while (true) {
		// every time read a frame from CAN
		nbytes = read(s, &frame, sizeof(can_frame));
		//frameNum++;

		if (nbytes < 0) {
		    perror("Read");
			return 1;
		}
		// explain this CAN frame's data  
		//frame.can_id >>= 3;

		//cout <<"I receive a " << frameNum++ << "frame" << endl;
		switch(frame.can_id) {
			case 0x50A: {
				cout << "receive 0x50A " << endl;

				//SR_CurrentSteeringAngle
				/*
				Signal Name	         Byte Order	Value Type	Start Bit	Length	Factor	Offset	Unit	Value Table	Comment

				SR_CurrentSteeringAngle	Intel	Unsigned	8	          14      0.1 	-600	deg		方向盘当前转角，左负右正

					decode version 1
				    CAN use little endian , 
					When we meet cross-byte signal we can left shift 8 bit of the second frame's bits  , then plus first frame's bits which we need .
					after that we make a & calculation to save the low bits which we need.
					finally we multiply the factor and plus the offset.
					*** note  that symbol "+"  has higher priority than  "<<" ***

				*/

				double CSA = ((((int)frame.data[2] << 8 ) + frame.data[1]) & ((2 << 14) - 1)) * 0.1 - 600;				
				cout << hex << CSA <<endl;


				/*
					decode version 2
					
					bitset<14> csa = ((frame.data[2] <<2 ) >> 2);
					csa = (csa.to_ulong() << 8) + frame.data[1];
					cout << csa.to_string() << endl;
					double CSA = -600 + 0.1 * (int)(csa.to_ulong());
				*/

				if (CSA < 0) {
					cout << "current steering Angle is left " << -1*CSA <<" deg" <<endl;
				} else {
					cout << "current steering Angle is right " << CSA << " deg" <<endl;
				}

				sr.SR_CurrentSteeringAngle = CSA;



				//SR_CurrentSteeringSpeed
				
				double CSS = ((frame.data[3] << 8) + (frame.data[2] >> 6)) & ((2 << 10) - 1);

				
				cout << "current steering speed is " << CSS << " deg/s" << endl;
				sr.SR_CurrentSteeringSpeed = CSS;

				//SR_HandTorque
				double HT = (((frame.data[5] << 8) + frame.data[4]) & ((2 << 10) - 1)) * 0.01;
				cout << "current HandTorque is " << HT << "NM" << endl;
				sr.SR_HandTorque = HT;

				// SR_HandTorqueSign
				int HTS = (int) ((frame.data[5] >> 2) & 1);
				sr.SR_HandTorqueSign = HTS;
				if(HTS == 0){
					cout << "current HandTorqueSign is Left" << endl;
				}
				else{
					cout << "current HandTorqueSign is Right" << endl;
				}
				//sr.SR_CurrentSteeringAngle = (uint8_t)frame.data[1]*

				//SR_WorkMode
				int WM = (int) ((frame.data[5] >> 3) & ((2 << 3) - 1));
				sr.SR_WorkMode = WM;
				if(WM == 0)
				{
					cout << "WorkMode is Manual" << endl; 
				}
				else if(WM == 1)
				{
					cout << "WorkMode is Angle" << endl; 
				}
				else if(WM == 2)
				{
					cout << "WorkMode is Torque" << endl; 
				}
				else if(WM == 7)
				{
					cout << "WorkMode Error" << endl; 
				}

				//SR_HandTorqueLimit

				double HTL = (((frame.data[6] << 8) + (frame.data[5] >> 6)) & ((2 << 10) - 1)) * 0.01;
				sr.SR_HandTorqueLimit = HTL;
				cout << "current HandTorqueLimit is " << HTL << " NM" << endl;
				//SR_Error
				int err = frame.data[7] & 3;
				sr.SR_Error = err;
				if(err == 0)
				{
					cout << "error signal is NoError" << endl;
				}
				else if(err == 1)
				{
					cout << "error signal is OverCurrent " << endl;
				}
				else if(err ==2)
				{
					cout << "error signal is LoseSAS " << endl;
				}

				//waring
				int waring = ((frame.data[7] >> 2 ) & 3);
				sr.SR_Waring = waring; 
				if(waring == 0)
				{
					cout << "waring signal is None waring" << endl;
				}
				else if(waring == 1)
				{
					cout << "waring signal is LeftLimit" <<endl;
				}
				else if(waring == 2)
				{
					cout << "waring signal is RightLimit" <<endl;
				}
				
				//liveCounter
				double lc = (frame.data[7] >> 4) & ((2 << 4) - 1) ;
				sr.SR_LiveCounter = lc;
				cout << "LiveCounter is " << lc << endl;
				//print a frame's data in hex
				for (int i = 0; i < frame.can_dlc; i++) {
					cout << std::hex << (int)frame.data[i] << " "; 
				}
				break;
			}

		}
		cout << endl;
		//receive a frame in 20ms
		usleep(200000);
	}

	//close socket file
	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
