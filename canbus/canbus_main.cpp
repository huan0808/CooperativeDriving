#include <ctime>
#include <iostream>

#include "can_reader.hpp"
#include "steering_report.hpp"
#include "chassis_report.hpp"

#define CANBUS_T 0.02

int main(int argc, char **argv) {
    std::cout << " ========= Starting Canbus Module =========== " << std::endl;
    CanReader can_reader;
    while (true) {
        clock_t start_t = clock();
        SteeringReport str_report;
        if (!can_reader.read_steering_report(&str_report)) {
            std::cout << "Read steering report failed!" << std::endl;
        };
        ChassisReport chas_report;
        if(!can_reader.read_chassis_report(&chas_report)) {
            std::cout << "Read chassis report failed!" << std::endl;
        };
        clock_t end_t = clock();
        const double elapsed_t = static_cast<double>((end_t - start_t) / CLOCKS_PER_SEC);
        if (elapsed_t < CANBUS_T) {
            sleep(CANBUS_T - elapsed_t);
        } else {
            std::cout << "Warning: canbus loop spent " << elapsed_t << " seconds" << std::endl;
        }
    }
}