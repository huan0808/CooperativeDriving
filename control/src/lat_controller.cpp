#include "lat_controller.hpp"

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <limits>

#include "math_utils.hpp"

#define PATH_LEN 16201 // TODO(huan): change this length based on the actual path file
#define SEARCH_GAP 500

LatController::LatController() {
    // load ref path
    // TODO(huan): change the path file here
    char file_name[] = "xxxxx/control/data/vehicle_log__xxxx.csv";
    // TODO(huan): change the path length here
    ref_path_.reserve(PATH_LEN);
    FILE* path_file = fopen(file_name, "r");
    if (path_file == nullptr) {
        std::cout << "Fail to open path file:" << file_name << std::endl;
    } else {
        char dummy_header_0[30];
        char dummy_header_1[30];
        char dummy_header_2[30];
        char dummy_header_3[30];
        char dummy_header_4[30];
        char dummy_header_5[30];
        char dummy_header_6[30];
        fscanf(path_file, "%s %s %s %s %s %s %s", 
               dummy_header_0, dummy_header_1, dummy_header_2, dummy_header_3, dummy_header_4, dummy_header_5, dummy_header_6);
        for (int i = 0; i < PATH_LEN; i++) {
            double t, x, y, theta, speed, steer_angle, front_steer_angle;
            fscanf(path_file, "%lf %lf %lf %lf %lf %lf %lf", &t, &x, &y, &theta, &speed, &steer_angle, &front_steer_angle);
            // original theta [0, 360) degrees, pointing to North as zero, increasing clockwise
            // transform theta to (-pi, pi] radians, pointing to East as zero, increasing counter clockwise
            theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);
            // transform steer_angle to radians
            steer_angle = steer_angle / 180.0 * M_PI;
            ref_path_.emplace_back(x, y, theta, steer_angle);
        }
        fclose(path_file);
        path_file = nullptr;
        has_path_ = true;
        // print ref path for debug
        // for (int i = 0; i < 10; i++) {
        //     std::cout << std::fixed << "path point " << i
        //               << " x: " << ref_path_[i].x
        //               << " y: " << ref_path_[i].y
        //               << " theta: " << ref_path_[i].theta << std::endl;
        // }
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
        if (min_squared_dist > 4.0) {
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
    const double ref_x = ref_path_[path_point_index_].x;
    const double ref_y = ref_path_[path_point_index_].y;
    const double ref_theta = ref_path_[path_point_index_].theta;
    const double ref_steer_angle = ref_path_[path_point_index_].steer_angle;

    const double dx = x - ref_x;
    const double dy = y - ref_y;
    const double cos_ref_heading = std::cos(ref_theta);
    const double sin_ref_heading = std::sin(ref_theta);
    const double lateral_error = cos_ref_heading * dy - sin_ref_heading * dx;
    // transform theta to (-pi, pi] radians, pointing to East as zero, increasing counter clockwise
    theta = NormalizeAngle(M_PI_2 - theta / 180.0 * M_PI);
    const double heading_error = NormalizeAngle(theta - ref_theta);
    const double k_lat = 0.2;
    const double k_heading = 1;
    const double steer_angle_desired = -k_lat * lateral_error - k_heading * heading_error + ref_steer_angle;

    // compute the steering torque command
    // steering_torque = -k_torque * steering_angle_error
    // transform current steering angle to radians
    const double curr_steer_angle = curr_steer_angle / 180.0 * M_PI;
    const double steer_angle_error = steer_angle_desired - curr_steer_angle;
    // torque in 2-5 NM
    const double k_torque = 50.0;
    double steer_torque_command = -k_torque * steer_angle_error;
    steer_torque_command = Clamp(steer_torque_command, -5.0, 5.0);
    sequence_++;

    return steer_torque_command;
}