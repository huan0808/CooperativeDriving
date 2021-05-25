#pragma once

struct ControlByWire {
    double CBW_AX_Request = 0.0; // accecel command [m/s^2]
    int CBW_AccelerationRequestSt = 0; // 0-NoRequest, 1-ACCRequest, 2-AEBRequest
    int CBW_FunctionRequestSt = 0; // 0-NoRequest, 1-Request
    int CBW_GearRequest = 0; // 0-NoRequest, 1-P, 2-R, 3-N, 4-D
    int CBW_StandStillRequest = 0; // 0-NoRequest, 1-Request
    int CBW_LeftLightRequest = 0; // 0-NoRequest, 1-Off, 2-On
    int CBW_RightLightRequest = 0; // 0-NoRequest, 1-Off, 2-On
    int CBW_HazardLightRequest = 0; // 0-NoRequest, 1-Off, 2-On
    int CBW_EPBRequest = 0; // 0-NoRequest, 1-Releasing, 2-Locking
    int CBW_LiveCounter = 0;
};