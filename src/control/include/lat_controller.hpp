// Date: 20201209 22:24
// version 1.0
// modified by lwy [20201209-22-24]

#pragma once
#include <vector>
#include <iostream>

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
 
private:

    int sequence_ = 0;
    std::vector<PathPoint> ref_path_;
    bool has_path_ = false;
    bool init_position_good_ = true;

private:
	int path_point_index_ = -99;
	double lateral_error = -99.0;
	double heading_error = -99.0;
	double torque = -99.0;
	double ref_heading = -99.0;

public:
	int get_path_point_index() {
		if (path_point_index_ == -99) {
			std::cerr << "# INIT ERROR #  path_point_index = -99" << std::endl;
		}
		return path_point_index_;
	}

	double get_lateral_error() {
		if (lateral_error == -99.0) {
			std::cerr << "# INIT ERROR #  lateral_error = -99.0" << std::endl;
		}
		return lateral_error;
	}

	double get_heading_error() {
		if (heading_error == -99.0) {
			std::cerr << "# INIT ERROR #  heading_error = -99.0" << std::endl;
		}
		return heading_error;
	}

	double get_torque() {
		if (torque == -99.0) {
			std::cerr << "# INIT ERROR #  torque = -99.0" << std::endl;
		}
		return torque;
	}

	double get_ref_heading() {
		if (ref_heading == -99.0) {
			std::cerr << "# INIT ERROR #  ref_heading = -99.0" << std::endl;
		}
		return ref_heading;
	}
};
