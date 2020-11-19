#include <math.h>
#include "math_utils.hpp"
double WrapAngle(const double angle) {
    const double new_angle = std::fmod(angle, M_PI * 2.0);
    return new_angle < 0 ? new_angle + M_PI * 2.0 : new_angle;
}

double NormalizeAngle(const double angle) {
    double a = std::fmod(angle + M_PI, 2.0 * M_PI);
    if (a < 0.0) {
        a += (2.0 * M_PI);
    }
    return a - M_PI;
}
