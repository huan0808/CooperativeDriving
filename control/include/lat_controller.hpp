#pragma once
#include <vector>

class LatController {
struct PathPoint {
    PathPoint(double x, double y, double theta, double steer_angle)
    :x(x), y(y), theta(theta), steer_angle(steer_angle){};
    double x; // point to East
    double y; // point to North
    double theta; // [radian], point to East as zero
    double steer_angle; // [radian], left positive

};
public:
    LatController();
    ~LatController() = default;
    double ComputeSteerTorque(double x, double y, double theta, double curr_steer_angle);
    double ComputeSteerAngle(double x, double y, double theta, double curr_steer_angle);
    bool has_path() { return has_path_;}
    int path_point_index_ = 0;
    double lateral_error = 0;
    double heading_error = 0; 
private:

    int sequence_ = 0;
    std::vector<PathPoint> ref_path_;
    bool has_path_ = false;
    bool init_position_good_ = true;
};