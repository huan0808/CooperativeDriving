#pragma once

#define UNSET_DOUBLE -99.99
#define UNSET_INT -99

struct SteeringReport {
    double SR_CurrentSteeringAngle = UNSET_DOUBLE;
    double SR_CurrentSteeringSpeed = UNSET_DOUBLE;
    double SR_HandTorque = UNSET_DOUBLE;
    int SR_HandTorqueSign = UNSET_INT;
    int SR_WorkMode = UNSET_INT;
    double SR_HandTorqueLimit = UNSET_DOUBLE;
    int SR_Error = UNSET_INT;
    int SR_Warning = UNSET_INT;
    double SR_LiveCounter = UNSET_DOUBLE;
};