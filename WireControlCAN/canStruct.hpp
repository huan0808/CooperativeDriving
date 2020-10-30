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
};

class SteeringControl
{
public:
    int SC_SteeringControlRequest;
    double SC_TargetSteeringAngle;
    double SC_TargetSteeringSpeed;
    double SC_TargetTorque;
    double SC_TargetTorqueSign;
    double SC_SetHandTorqueLimitValid;
    double SC_SetHandTorqueLimit;
    double SC_LiveCounter;
};