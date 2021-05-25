#include "lat_controller.hpp"
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <limits>

#include "math_utils.hpp"

#define PATH_LEN 2471  // TODO(huan): change this length based on the actual path file
#define SEARCH_GAP 500

LatController::LatController() 
{
    // load ref path
    // TODO(huan): change the path file here
    char file_name[] = "/home/nvidia/tmp/jluData/reference/15kmFuzzyPID2.csv";
    // TODO(huan): change the path length here
    ref_path_.reserve(PATH_LEN);
    FILE* path_file = fopen(file_name, "r");
    if (path_file == nullptr)
    {
        std::cout << "Fail to open path file:" << file_name << std::endl;
    } 
    else 
    {
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
        
		for (int i = 0; i < PATH_LEN; i++) 
        {
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
            steer_angle = steer_angle / 180.0 * M_PI; // �������Ѿ������˴������ǻ�����
            ref_path_.emplace_back(x, y, theta, steer_angle); //get the reference path here
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
	lateral_error = 0.0;
	preview_point = 20; // 65   with preview: 27
	preview_percent = 0.945; //0.92
	heading_P = 1.25; //2
	PID_percent = 1.0;
        //               kp   kd   e_b  ec_b ukp_b ukd_b 
	myPID = FuzzyPID(0.9, 0.2, 0.42, 0.175, 0.2, 0.08); // the best now 2021.01.16 //fuzzy p 0.2
                    // T    Kp7.5     Kd0.3    B    W
        // myADRC = ADRC(0.0482, 6.6, 0.375, 0.8, 1.4);    // linear combine,2021.04.28
	myADRC = ADRC(0.0482, 6.6,  0.375, 0.8, 1.4);    // linear combine,2021.04.28
	falPa0 = 0.27, falDa1 = 1.25, deta = 0.5;
        fhanh = 1.15, fhanc = 0.03, fhanr = 500;
    }
}

/*
 *@brief: change this function for ADRC and FuzzyPID
 * the curr_steer_angle is angle, need to be rad
 */
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
        if (min_squared_dist > 100.0) { // 4.0
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
	
	// int preview_point = 50;//20
	const double ref_x = ref_path_[path_point_index_ + preview_point].x;
	const double ref_y = ref_path_[path_point_index_ + preview_point].y;
	const double ref_theta = ref_path_[path_point_index_ + preview_point].theta;
	const double ref_steer_angle = ref_path_[path_point_index_ + preview_point].steer_angle;


	const double dx = x - ref_x;
	const double dy = y - ref_y;
	const double cos_ref_heading = std::cos(ref_theta);
	const double sin_ref_heading = std::sin(ref_theta);

	theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);
	heading_error = NormalizeAngle(theta - ref_theta);
	ref_heading = theta;

	lateral_error = std::cos(ref_path_[path_point_index_].theta) * (y - ref_path_[path_point_index_].y) - std::sin(ref_path_[path_point_index_].theta) * (x - ref_path_[path_point_index_].x);
	const double lateral_error_1 = cos_ref_heading * dy - sin_ref_heading * dx;
	// double loop for control�� the ref_steer_angle is rad, no 	-+ 
	const double steer_Rad_desired = PID_percent * myPID.CalculatePIDOutput(lateral_error_1) + preview_percent * ref_steer_angle + heading_P * heading_error + 3.0/180* M_PI; // 3 is because of the steering wheel 
	const double steerRad = curr_steer_angle / 180 * M_PI;
   	// double steer_torque_command = - myADRC.ComputeWithLinearFeedback(steer_Rad_desired, steerRad); // linear like PID compute
   	// fal nonlinear compute                                                   falPa0  falDa1  deta
        double steer_torque_command = - myADRC.ComputeWithFalFeedback(steer_Rad_desired, steerRad, falPa0, falDa1, deta);
    // fhan nonlinear compute                                                                      fhanh fhanc  fhanr
        // double steer_torque_command = - myADRC.ComputeWithFhanFeedback(steer_Rad_desired, steerRad, fhanh, fhanc, fhanr);

	steer_torque_command = Clamp(steer_torque_command, -5.0, 5.0);
	torque = steer_torque_command;
	sequence_++;
	return steer_torque_command;
}

/*
 * this hasn't been changed for fuzzyPId angle control
 */
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
        if (min_squared_dist > 100.0) { // 16.0
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
    // int preview_point = 50;//20
    const double ref_x = ref_path_[path_point_index_ + preview_point].x;
    const double ref_y = ref_path_[path_point_index_ + preview_point].y;
    const double ref_theta = ref_path_[path_point_index_ + preview_point].theta;
    // const double ref_steer_angle = ref_path_[path_point_index_ + preview_point].steer_angle;
    const double ref_steer_angle = ref_path_[path_point_index_ + preview_point].steer_angle;


    const double dx = x - ref_x;
    const double dy = y - ref_y;
    const double cos_ref_heading = std::cos(ref_theta);
    const double sin_ref_heading = std::sin(ref_theta);

    theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);
    heading_error = NormalizeAngle(theta - ref_theta);
    ref_heading = theta;
    
    lateral_error = std::cos(ref_path_[path_point_index_].theta) * (y - ref_path_[path_point_index_].y) - std::sin(ref_path_[path_point_index_].theta) * (x - ref_path_[path_point_index_].x);
	const double lateral_error_1 = cos_ref_heading * dy - sin_ref_heading * dx;
    	// double loop for control
    const double steer_angle_desired = PID_percent * myPID.CalculatePIDOutput(lateral_error_1) + preview_percent * ref_steer_angle + heading_P * heading_error; // 3 is because of the steering wheel 

	// const double steer_angle_desired = 50 * lateral_error_1;
	std::cout << " lateral error: " << lateral_error_1 << std::endl;
    const double k_lat = 0.175; //0.15
    const double k_heading = 2.5; //2.5

    const double k_d_lat = 0.01; //0.01
    const double k_d_heading = 0; //0



    sequence_++;
    return  steer_angle_desired * 180 / M_PI + 3.0; // +3
}
