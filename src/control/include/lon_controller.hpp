#pragma once

#include <iostream>

#include "pid_controller.hpp"

class LonController {
 public:
  LonController();
  ~LonController() = default;
  double ComputeAccel(double curr_speed, double ts);
  void SetCruiseSpeed(double cruise_speed) {
    if (cruise_speed < 0 || cruise_speed > 40) {
      std::cout << "Cruise speed < 0 or > 40 kph!" << std::endl;
      cruise_speed_ = 0.0;
    } else {
      cruise_speed_ = cruise_speed;
    }
  };

 private:
  PIDController pid_controller_;
  double cruise_speed_;  // km/h
  double target_speed_;
  int sequence_ = 0;
};