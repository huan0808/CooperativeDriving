#pragma once

#include "lon_controller.hpp"

#include <cmath>

LonController::LonController() {
  // TODO(huan): tune kp and ki
  PidConf pid_conf;
  pid_conf.integrator_enable = true;
  pid_conf.integrator_saturation_level = 0.3;
  pid_conf.kp = 1.0;
  pid_conf.ki = 1.0;
  pid_conf.kd = 0.0;
  pid_controller_.Init(pid_conf);
}

double LonController::ComputeAccel(double curr_speed, double ts) {
  // make target speed start from zero and approach cruise speed at a constant
  // growth rate
  const double target_speed_accel = 0.5;  // m/s^2
  target_speed_ = std::min(sequence_++ * ts * target_speed_accel, cruise_speed_ / 3.6);

  const double speed_error = target_speed_ - curr_speed;
  const double accel_cmd = pid_controller_.Control(speed_error, ts);

  return accel_cmd;
}
