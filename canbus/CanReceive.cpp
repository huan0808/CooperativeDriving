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
using namespace std;

void printHexData(can_frame &frame)
{
	for (int i = 0; i < frame.can_dlc; i++) {
		cout << hex << (int)frame.data[i] << " ";
	}

}


int main(int argc, char **argv)
{


	cout << "CAN Sockets Receive Demo." << endl;

	// create a socket file descriptor
	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
		perror("Socket");
		return 1;
	}
	cout << "Receiver's linux file descriptor is " << s << endl;

    //copy c string to ifr (network device)
	// standard ioctls of network device 
    ifreq ifr;
	strcpy(ifr.ifr_name, "can0");  
	//system call manipulates the underlying device parameters of special files             
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

				
				/*

				    CAN use little endian , 
					When we meet cross-byte signal we convert second byte to int and left shift 1-8 bit , then plus first frame's bits which we need .
					after that we make a & calculation to save the low bits we need.
					finally we multiply the factor and plus the offset.
					*** note  that symbol "+"  has higher priority than  "<<" ***

				*/
				
				//SR_CurrentSteeringAngle

				double CSA = ((((int)frame.data[2] << 8 ) + frame.data[1]) & ((1 << 14) - 1)) * 0.1 - 600;				
				cout << hex << CSA <<endl;


				if (CSA < 0) {
					cout << "current steering Angle is left " << -1*CSA <<" deg" <<endl;
				} else {
					cout << "current steering Angle is right " << CSA << " deg" <<endl;
				}

				sr.SR_CurrentSteeringAngle = CSA;



				//SR_CurrentSteeringSpeed
				
				double CSS = (((int)frame.data[3] << 2) + (frame.data[2] >> 6)) & ((1 << 10) - 1);

				
				cout << "current steering speed is " << CSS << " deg/s" << endl;
				sr.SR_CurrentSteeringSpeed = CSS;

				//SR_HandTorque
				double HT = ((((int)frame.data[5] << 8) + frame.data[4]) & ((1 << 10) - 1)) * 0.01;
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
				
				//SR_WorkMode
				int WM = (int) ((frame.data[5] >> 3) & ((1 << 3) - 1));
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

				double HTL = ((((int)frame.data[6] << 2) + (frame.data[5] >> 6)) & ((1 << 10) - 1)) * 0.01;
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
				double lc = (frame.data[7] >> 4) & ((1 << 4) - 1) ;
				sr.SR_LiveCounter = lc;
				cout << "LiveCounter is " << lc << endl;
				//print a frame's data in hex
				printHexData(frame);
				break;
			}
			case 0x68F:
			{
				cout << "receive 0x68F" << endl;

				//GearInfo
				int GI = frame.data[0] & ((1 << 3) - 1);



				if(GI == 0)
				{
					cout << " Gear singal is P " << endl;
				}
				else if (GI == 1)
				{
					cout << " Gear singal is R " << endl;
				}
				else if (GI == 2)
				{
					cout << " Gear singal is N " << endl;
				}
				else if (GI == 3)
				{
					cout << " Gear singal is D " << endl;
				}
				//sr.VI_GearInfo = GI;

				//BrakeInfo
				int BI = ((frame.data[0] >> 3 ) & 1 );
				if (BI == 0)
				{
					cout << " Brake singal is NoBrake " << endl;
				}
				else if (BI == 1)
				{
					cout << " Brake singal is Brake " << endl;
				}
				//sr.VI_BrakeInfo = BI;

				//Button1
				int B1 = (frame.data[0] >> 4 ) & 1 ;
				if (B1 == 0)
				{
					cout << " Button1 is NoPress " << endl;
				}
				else if (B1 == 1)
				{
					cout << " Button1 is Press " << endl;
				}
				//sr.VI_Button1 = B1;

				//Button2
				int B2 =  (frame.data[0] >> 5 ) & 1 ;
				if (B2 == 0)
				{
					cout << " Button2 is NoPress " << endl;
				}
				else if (B2 == 1)
				{
					cout << " Button2 is Press " << endl;
				}
				//sr.VI_Button2 = B2;

				//HandBrakeSt
				int HBS = (frame.data[0] >> 6) & 1 ;
				if (HBS == 0)
				{
					cout << " HandBrakeSt singal is NoBrake " << endl;
				}
				else if (HBS == 1)
				{
					cout << " HandBrakeSt singal is Brake " << endl;
				}
				//sr.VI_HandBrakeSt = HBS;

				//JerkSt
				int JS = (frame.data[0] >> 7) & 1;
				if (JS == 0)
				{
					cout << " JerkSt is NoPress " << endl;
				}
				else if (JS == 1)
				{
					cout << " JerkSt is Press " << endl;
				}
				//sr.VI_JerkSt = JS;

				//AccelPedalPosition
				double APP = (frame.data[1] & ((1 << 8) - 1)) * 0.4;
				cout << " Accel PedalPosition is " << APP << " % " << endl;
				//sr.VI_AccelPedalPosition = APP;

				//FrontSteeringAngle
				double FSA = ((((int)frame.data[3] << 8) + frame.data[2]) & ((1 << 16) - 1)) * 0.1 - 600;
				cout << " Front Steering Angle is " << FSA << " deg " << endl;
				//sr.VI_FrontSteeringAngle = FSA;

				//RemainingTimes
				double RT = (((int)frame.data[5] << 8) + frame.data[4]) & ((1 << 12) - 1);
				cout << " Remaining Times is " << RT << " s " << endl;
				//sr.VI_RemainingTimes = RT;

				//VehicleSpeed
				double VS = ((((int)frame.data[7] << 8) + frame.data[6]) & ((1 << 16) - 1)) * 0.01;
				cout << " Vehicle Speed is " << VS << " km/h " << endl;
				//sr.VI_VehicleSpeed = VS;
				printHexData(frame);

				break;
			}

			case 0x68A:
			{
				cout << "receive 0x68A" << endl;

				//LongitudinalAccel
				double LoA = ((((int)frame.data[1] << 8) + frame.data[0]) & ((1 << 12) - 1)) * 0.01 - 20;
				cout << " Longitudinal Acceleration is " << LoA << " m/s2 " << endl;
				//sr.SI2_LongitudinalAccel = LoA;
				
				//LateralAccel
				double LaA = ((((int)frame.data[2] << 4) + (frame.data[1] >> 4) & ((1 << 12) - 1)) * 0.01 - 20);
				cout << " Lateral Acceleration is "  << LaA << " m/s2 " << endl;
				//sr.SI2_LateralAccel = LaA;
				
				//YawRate
				double YR = ((((int)frame.data[4] << 8) + frame.data[3]) & ((1 << 12) - 1)) * 0.05 - 100;
				cout << " Yaw Rate is " << YR << " deg/s " << endl;
				//sr.SI2_YawRate = YR;

				printHexData(frame);
				break;
			}

		}
		cout << endl;
		//receive a frame in 20ms
		usleep(20000);
	}

	//close socket file
	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
