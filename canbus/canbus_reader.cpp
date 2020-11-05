#include "can_reader.hpp"

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

bool CanBusReader::read_steering_report(SteeringReport* const steering_report) {
  	int s = 0;
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
		perror("Socket");
		return false;
	}
    
}

bool CanBusReader::read_chassis_report(ChassisReport* const chassis_report) {

}