#pragma once

struct ChassisReport {
    int VI_GearInfo = 0;
    int VI_BrakeInfo = 0;
    int VI_Button1 = 0;
    int VI_Button2 = 0;
    int VI_HandBrakeSt = 0;
    int VI_JerkSt = 0;
    double VI_AccelPedalPosition = 0.0;
    double VI_FrontSteeringAngle = 0.0;
    double VI_RemainingTimes = 0.0;
    double VI_VehicleSpeed = 0.0;
    double SI2_LongitudinalAccel = 0.0;
    double SI2_LateralAccel = 0.0;
    double SI2_YawRate = 0.0;
};
