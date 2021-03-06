#pragma once

struct SteeringControl {
    int SC_SteeringControlRequest = 0; // 0-No Request, 1-Torque Request, 2-Angle Request, 3-Reserved
    int SC_TargetSteeringAngle = 0.0; // [deg]
    int SC_TargetSteeringSpeed = 0.0; // [deg/s]
    double SC_TargetTorque = 0.0; // [Nm]
    int SC_TargetTorqueSign = 0; // 0-Left, 1-Right
    int SC_SetHandTorqueLimitValid = 0; // 0-Invalid, 1-Valid
    double SC_SetHandTorqueLimit = 3.0; // [Nm]
    int SC_LiveCounter = 0.0;
};
