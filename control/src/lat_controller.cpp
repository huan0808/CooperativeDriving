// Date: 20201209 22:57
// version 1.0
// modified by lwy [20201209-22-57]

#include "lat_controller.hpp"

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <limits>

#include "math_utils.hpp"

#define PATH_LEN 3000  // TODO(huan): change this length based on the actual path file
#define SEARCH_GAP 500

LatController::LatController() {
    // load ref path
    // TODO(huan): change the path file here
    char file_name[] = "/home/nvidia/tmp/Cooperative Driving/reference/15kmh_version1.0.csv";
    // TODO(huan): change the path length here
    ref_path_.reserve(PATH_LEN);
    FILE* path_file = fopen(file_name, "r");
    if (path_file == nullptr) {
        std::cout << "Fail to open path file:" << file_name << std::endl;
    } else {
		// read csv header
        char dummy_header_0[30];
        char dummy_header_1[30];
        char dummy_header_2[30];
        char dummy_header_3[30];
        char dummy_header_4[30];
        char dummy_header_5[30];
        char dummy_header_6[30];
        char dummy_header_7[30];
        char dummy_header_8[30];
        char dummy_header_9[30];
        char dummy_header_10[30];
        char dummy_header_11[30];
        fscanf(path_file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", 
               dummy_header_0, dummy_header_1, dummy_header_2, dummy_header_3, dummy_header_4,dummy_header_5,dummy_header_6,dummy_header_7,dummy_header_8,dummy_header_9,dummy_header_10,dummy_header_11);
        
		for (int i = 0; i < PATH_LEN; i++) {
            double t, x, y, theta, speed, steer_angle, front_steering_angle,lateral_error,heading_error,torque,ref_heading;
			int index;
            fscanf(path_file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf,%lf,%lf,%lf", &t, &x, &y, &theta, &speed, &steer_angle, &front_steering_angle,&index,&lateral_error,&heading_error,&torque,&ref_heading);

            /*
            std::cout << i << std::endl;
            std::cout << std::fixed << "path point " << i
                       << " x: " << x
                       << " y: " << y
                       << " theta: " << theta << "steerangle" << steer_angle << std::endl;
            */
            // original theta [0, 360) degrees, pointing to North as zero, increasing clockwise
            // transform theta to (-pi, pi] radians, pointing to East as zero, increasing counter clockwise
            //theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI); // 
            // transform steer_angle to radians
            steer_angle = steer_angle / 180.0 * M_PI;
            ref_path_.emplace_back(x, y, theta, steer_angle);   
        }
        fclose(path_file);
        path_file = nullptr;
        has_path_ = true;
        // print ref path for debug
 	/*
         for (int i = 0; i < 10; i++) {
             std::cout << std::fixed << "path point " << i
                       << " x: " << ref_path_[i].x
                       << " y: " << ref_path_[i].y
                       << " theta: " << ref_path_[i].theta << "steerangle" << std::endl;
         }
	*/
    }
}

double LatController::ComputeSteerTorque(double x, double y, double theta, double curr_steer_angle) {
    // compute steer torque based current position and ref path
    // do not send control if ref path is not loaded
    if (!has_path_) {
        std::cout << "There is no path !" << std::endl;
        return 0.0;
    }
    
    // find the closet path point as the reference path point
    // for the first loop, find the closest path point from the start
    if (sequence_ == 0) {
        double min_squared_dist = std::numeric_limits<double>::infinity();
        for (int i = 0; i < PATH_LEN; i++) {
            const double squared_dist = (x - ref_path_[i].x) * (x - ref_path_[i].x) +
                                            (y - ref_path_[i].y) * (y - ref_path_[i].y);
            if (squared_dist < min_squared_dist) {
                min_squared_dist = squared_dist;
                path_point_index_ = i;
            }
        }
        if (min_squared_dist > 9.0) { // 4.0
            // do not send control if car init position too far from ref path
            // should move the car and restart program
            std::cout << "Car init position too far from ref path, do not send control. "
                      << " x: " << x << " y: " << y
                      << " path_index: " << path_point_index_
                      << " ref_x: " << ref_path_[path_point_index_].x
                      << " ref_y: " << ref_path_[path_point_index_].y << std::endl;
            init_position_good_ = false;
            return 0.0;
        }
    } else {
        // 
        if (!init_position_good_) {
            // do not send control if car init position too far from ref path
            // should move the car and restart program
            std::cout << "Car init position too far from ref path, do not send control. " << std::endl;
            return 0.0;
        } else {
            // from the second loop, find the closest path point near path_point_index_
            double min_squared_dist = std::numeric_limits<double>::infinity();
            for (int i = std::max(0, path_point_index_ - SEARCH_GAP);
                i < std::min(PATH_LEN, path_point_index_ + SEARCH_GAP); i++) {
                const double squared_dist = (x - ref_path_[i].x) * (x - ref_path_[i].x) +
                                                (y - ref_path_[i].y) * (y - ref_path_[i].y);
                if (squared_dist < min_squared_dist) {
                    min_squared_dist = squared_dist;
                    path_point_index_ = i;
                }
            }
        }
    }
    
    // compute the desired steering angle
    // TODO(huan): please fine tune k_lat, k_heading and k_torque
    // steering_angle_desired = -k_lat * lat_error - k_heading * heading_error + ref_steer_angle
	
	int preview_point = 20;//10
	const double ref_x = ref_path_[path_point_index_ + preview_point].x;
	const double ref_y = ref_path_[path_point_index_ + preview_point].y;
	const double ref_theta = ref_path_[path_point_index_ + preview_point].theta;
	const double ref_steer_angle = ref_path_[path_point_index_ + preview_point].steer_angle;
	
	const double dx = x - ref_x;
	const double dy = y - ref_y;
	const double cos_ref_heading = std::cos(ref_theta);
	const double sin_ref_heading = std::sin(ref_theta);

	//add a overlook point
	const double L = 5;
	//const double lat_p_error  = ref_steer_angle - curr_steer_angle;

	lateral_error = std::cos(ref_path_[path_point_index_].theta) * (y - ref_path_[path_point_index_].y) - std::sin(ref_path_[path_point_index_].theta) * (x - ref_path_[path_point_index_].x);
	//lateral_error = std::sqrt(std::pow(x - ref_path_[path_point_index_].x, 2) + std::pow(y - ref_path_[path_point_index_].y, 2));
	const double lateral_error_1 = cos_ref_heading * dy - sin_ref_heading * dx;
	//const double lateral_error_2 = std::sqrt(dx * dx + dy * dy);
	// transform theta to (-pi, pi] radians, pointing to East as zero, increasing counter clockwise do not send control.  x: 4.90074e+06 y: 187164 path_index: 0 ref_x: 0 ref_y: 0

	theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);


	//heading_error is e_theta
	heading_error = NormalizeAngle(theta - ref_path_[path_point_index_].theta);

	static double last_lat_error = 0.0;
	static double last_heading_error = 0.0;
        static double last_steer_angle_error = 0.0;

	const double heading_error_1 = NormalizeAngle(theta - ref_theta);
	//std::cout << "###  " << theta << " " << ref_theta << " " << theta - ref_theta << " " << heading_error << std::endl; 
	const double k_lat = 0.15; //0.15
	const double k_heading = 2.5; //2.5

	const double k_d_lat = 0.01; //0.01
	const double k_d_heading = 0; //0

	const double lat_p_error = L * std::sin(heading_error);
	//lateral_error = cos_ref_heading * dy - sin_ref_heading * dx + L * std::sin(heading_error);
	//const double steer_angle_desired = k_lat * (lateral_error_1 + lat_p_error) + ref_steer_angle;

	// lateral_error > 0 at lane left, turn right, steer_angle_desired > 0
	// lateral_error < 0 at lane right, turn left, steer_angle_desired < 0

	// heading_error > 0, turn right, steer_angle_desired > 0
	// heading_error < 0, turn left, steer_angle_desired < 0
	//+-???
	const double steer_angle_desired = k_lat * lateral_error_1 + k_heading * heading_error_1 + 1*ref_steer_angle + k_d_lat * (lateral_error_1 - last_lat_error) - k_d_heading * (heading_error_1 - last_heading_error);

	last_lat_error = lateral_error_1;
	last_heading_error = heading_error_1;
	
    // compute the steering torque command
    // steering_torque = -k_torque * steering_angle_error
    // transform current steering angle to radians

	const double steer_angle = curr_steer_angle / 180.0 * M_PI;

	//note: steer angle: desired-current
        // steer_angle_desired < 0 at lane left, turn right
        // steer_angle_desired > 0 at lane right, turn left
        // steer
	const double steer_angle_error = steer_angle_desired + 3 / 180.0 * M_PI - steer_angle;

	// torque in 2-5 NM
	const double k_torque = 30.0; //35.0
        const double k_d_torque = 5.0;

	//k_torque > 0, 
	//k_torque < 0, 
        //steer torque command < 0, turn right
        //steer torque command > 0, turn left
	double steer_torque_command = -k_torque * steer_angle_error + k_d_torque * (steer_angle_error - last_steer_angle_error);

	steer_torque_command = Clamp(steer_torque_command, -5.0, 5.0);
	torque = steer_torque_command;
	ref_heading = ref_steer_angle;

        last_steer_angle_error = steer_angle_error;

	sequence_++;
	return steer_torque_command;

}



double LatController::ComputeSteerAngle(double x, double y, double theta, double curr_steer_angle) {
    // compute steer torque based current position and ref path
    // do not send control if ref path is not loaded
    if (!has_path_) {
        std::cout << "There is no path !" << std::endl;
        return 0.0;
    }
    
    // find the closet path point as the reference path point
    // for the first loop, find the closest path point from the start
    if (sequence_ == 0) {
        double min_squared_dist = std::numeric_limits<double>::infinity();
        for (int i = 0; i < PATH_LEN; i++) {
            const double squared_dist = (x - ref_path_[i].x) * (x - ref_path_[i].x) +
                                            (y - ref_path_[i].y) * (y - ref_path_[i].y);
            if (squared_dist < min_squared_dist) {
                min_squared_dist = squared_dist;
                path_point_index_ = i;
            }
        }
        if (min_squared_dist > 9.0) { // 16.0
            // do not send control if car init position too far from ref path
            // should move the car and restart program
            
            printf("Car init position too far from ref path, do not send control.\n");
            printf(" x: %.2f y:%.2f \n",x,y);
            printf("pathpoint's index is %d\n",path_point_index_);
            printf(" ref_x: %.2f ref_y: %.2f \n",ref_path_[path_point_index_].x,ref_path_[path_point_index_].y);
            /*
            std::cout << "Car init position too far from ref path, do not send control. "
                      << " x: " << x << " y: " << y
                      << " path_index: " << path_point_index_
                      << " ref_x: " << ref_path_[path_point_index_].x
                      << " ref_y: " << ref_path_[path_point_index_].y << std::endl;
            */
            init_position_good_ = false;
            return 0.0;
        }
    } else {
        // 
        if (!init_position_good_) {
            // do not send control if car init position too far from ref path
            // should move the car and restart program
            std::cout << "Car init position too far from ref path, do not send control. " << std::endl;
            return 0.0;
        } else {
            
            
            //const int pre_point_index = path_point_index_;
            // from the second loop, find the closest path point near path_point_index_
            double min_squared_dist = std::numeric_limits<double>::infinity();
            for (int i = std::max(0, path_point_index_ - SEARCH_GAP);
                i < std::min(PATH_LEN, path_point_index_ + SEARCH_GAP); i++) {
                const double squared_dist = (x - ref_path_[i].x) * (x - ref_path_[i].x) +
                                                (y - ref_path_[i].y) * (y - ref_path_[i].y);
                if (squared_dist < min_squared_dist) {
                    min_squared_dist = squared_dist;
                    path_point_index_ = i;
                }
            }
        }
    }
 
    //printf(" x: %.2f y:%.2f \n",x,y);
    //printf("pathpoint's index is %d\n",path_point_index_);
    //printf(" ref_x: %.2f ref_y: %.2f \n",ref_path_[path_point_index_].x,ref_path_[path_point_index_].y);
    // compute the desired steering angle
    // TODO(huan): please fine tune k_lat, k_heading and k_torque
    // steering_angle_desired = -k_lat * lat_error - k_heading * heading_error + ref_steer_angle
	int preview_point = 20;//20
    const double ref_x = ref_path_[path_point_index_ + preview_point].x;
    const double ref_y = ref_path_[path_point_index_ + preview_point].y;
    const double ref_theta = ref_path_[path_point_index_ + preview_point].theta;
    const double ref_steer_angle = ref_path_[path_point_index_ + preview_point].steer_angle;


    const double dx = x - ref_x;
    const double dy = y - ref_y;
    const double cos_ref_heading = std::cos(ref_theta);
    const double sin_ref_heading = std::sin(ref_theta);
    
    
    //add a overlook point
    const double L = 5;
    //const double lat_p_error  = ref_steer_angle - curr_steer_angle;

    lateral_error = std::cos(ref_path_[path_point_index_ ].theta) * (y - ref_path_[path_point_index_ ].y) - std::sin(ref_path_[path_point_index_ ].theta) * (x - ref_path_[path_point_index_ ].x);
	//lateral_error = std::sqrt(std::pow(x - ref_path_[path_point_index_].x, 2) + std::pow(y - ref_path_[path_point_index_].y, 2));
    const double lateral_error_1 = cos_ref_heading * dy - sin_ref_heading * dx;
	//const double lateral_error_2 = std::sqrt(dx * dx + dy * dy);
    // transform theta to (-pi, pi] radians, pointing to East as zero, increasing counter clockwise do not send control.  x: 4.90074e+06 y: 187164 path_index: 0 ref_x: 0 ref_y: 0

    theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);
    
    
    //heading_error is e_theta
    heading_error = NormalizeAngle(theta - ref_path_[path_point_index_].theta);

    static double last_lat_error = 0.0;
    static double last_heading_error = 0.0;

    const double heading_error_1 = NormalizeAngle(theta - ref_theta);
    //std::cout << "###  " << theta << " " << ref_theta << " " << theta - ref_theta << " " << heading_error << std::endl; 
    const double k_lat = 0.15; //0.15
    const double k_heading = 2.5; //2.5

    const double k_d_lat = 0.01; //0.01
    const double k_d_heading = 0; //0

    const double lat_p_error = L * std::sin(heading_error);
    //lateral_error = cos_ref_heading * dy - sin_ref_heading * dx + L * std::sin(heading_error);
    //const double steer_angle_desired = k_lat * (lateral_error_1 + lat_p_error) + ref_steer_angle;

    // lateral_error > 0 at lane left, turn right, steer_angle_desired > 0
    // lateral_error < 0 at lane right, turn left, steer_angle_desired < 0

    // heading_error > 0, turn right, steer_angle_desired > 0
    // heading_error < 0, turn left, steer_angle_desired < 0
    //+-???
    const double steer_angle_desired = k_lat * lateral_error_1 + k_heading * heading_error_1 + 0.925*ref_steer_angle + k_d_lat * (lateral_error_1 - last_lat_error) - k_d_heading * (heading_error_1 - last_heading_error);
    
    last_lat_error = lateral_error_1; 
    last_heading_error = heading_error_1;

    sequence_++;
    return  steer_angle_desired * 180 / M_PI + 3; // +3
}
