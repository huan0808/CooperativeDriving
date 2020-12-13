#pragma once

#define UNSET_DOUBLE -99.99
#define UNSET_INT -99

struct ChassisReport {
    int VI_GearInfo = UNSET_INT;
    int VI_BrakeInfo = UNSET_INT;
    int VI_Button1 = UNSET_INT;
    int VI_Button2 = UNSET_INT;
    int VI_HandBrakeSt = UNSET_INT;
    int VI_JerkSt = UNSET_INT;
    double VI_AccelPedalPosition = UNSET_DOUBLE;
    double VI_FrontSteeringAngle = UNSET_DOUBLE;
    double VI_RemainingTimes = UNSET_DOUBLE;
    double VI_VehicleSpeed = UNSET_DOUBLE;
    double SI2_LongitudinalAccel = UNSET_DOUBLE;
    double SI2_LateralAccel = UNSET_DOUBLE;
    double SI2_YawRate = UNSET_DOUBLE;
};
