#pragma once

struct SteeringControl {
    SteeringControl() = default;
    SteeringControl(const int mode, const double TargetAngle, const double TargetSpeed,
                    const double TargetTorque, const int TargetTorqueDir)
    : SC_SteeringControlRequest(mode),
      SC_TargetSteeringAngle(TargetAngle),
      SC_TargetSteeringSpeed(TargetSpeed),
      SC_TargetTorque(TargetTorque),
      SC_TargetTorqueSign(TargetTorqueDir) {}

    int SC_SteeringControlRequest = 0;
    double SC_TargetSteeringAngle = 0.0;
    double SC_TargetSteeringSpeed = 0.0;
    double SC_TargetTorque = 0.0;
    int SC_TargetTorqueSign = 0;
    double SC_SetHandTorqueLimitValid = 0.0;
    double SC_SetHandTorqueLimit = 3.0;
    double SC_LiveCounter = 0.0;
};
