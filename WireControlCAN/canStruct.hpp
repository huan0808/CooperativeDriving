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

class SteeringReport
{
public:
    double SR_CurrentSteeringAngle;
    double SR_CurrentSteeringSpeed;
    double SR_HandTorque;
    int SR_HandTorqueSign;
    int SR_WorkMode;
    double SR_HandTorqueLimit;
    int SR_Error;
    int SR_Waring;
    double SR_LiveCounter;
    /*
    int VI_GearInfo;
    int VI_BrakeInfo;
    int VI_Button1;
    int VI_Button2;
    int VI_HandBrakeSt;
    int VI_JerkSt;
    double VI_AccelPedalPosition;
    double VI_FrontSteeringAngle;
    double VI_RemainingTimes;
    double VI_VehicleSpeed;
    double SI2_LongitudinalAccel;
    double SI2_LateralAccel;
    double SI2_YawRate;
    */

};

class SteeringControl
{
public:
    SteeringControl() = default;
    SteeringControl(int mode, double TargetAngle, double TargetSpeed,double TargetTorque,int TargetTorqueDir):
    SC_SteeringControlRequest(mode),SC_TargetSteeringAngle(TargetAngle),SC_TargetSteeringSpeed(TargetSpeed),
    SC_TargetTorque(TargetTorque){}

    int SC_SteeringControlRequest;
    double SC_TargetSteeringAngle;
    double SC_TargetSteeringSpeed;
    double SC_TargetTorque;
    double SC_TargetTorqueSign;
    double SC_SetHandTorqueLimitValid = 0;
    double SC_SetHandTorqueLimit = 3;
    double SC_LiveCounter = 0;

    void control();
    void SetThreshold();
    void sendFrame();
};

void ControlSteer(int mode, double TargetAngle, double TargetSpeed,double TargetTorque,int TargetTorqueDir)
{
    SteeringControl * sc = new SteeringControl(mode, TargetAngle, TargetSpeed,TargetTorque,TargetTorqueDir);
    
}