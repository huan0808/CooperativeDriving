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

void CanReader::read_steering_report(SteeringReport* const steering_report) {

}

void CanReader::read_chassis_report(ChassisReport* const chassis_report) {

}