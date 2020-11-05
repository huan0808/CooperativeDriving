#pragma once

struct SteeringReport {
    double SR_CurrentSteeringAngle = 0.0;
    double SR_CurrentSteeringSpeed = 0.0;
    double SR_HandTorque = 0.0;
    int SR_HandTorqueSign = 0;
    int SR_WorkMode = 0;
    double SR_HandTorqueLimit = 0.0;
    int SR_Error = 0;
    int SR_Waring = 0;
    double SR_LiveCounter = 0.0;
};