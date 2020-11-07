#include <chrono>
#include <iostream>
#include <thread>

#include "control_sender.hpp"

#define CONTROL_T 0.02 // in seconds

int main(int argc, char **argv) {
    using namespace std;

    cout << " ========= Starting Control Module =========== " << endl;
    ControlSender control_sender;
    if (!control_sender.InitSocket()) {
        cout << "Init socket failed" << endl;
        return 1;
    } else {
        cout << "Init socket success" << endl;
    }

    while (true) {
        const auto start_t = chrono::system_clock::now();
        const double steering_angle_command = -10.0;
        control_sender.ControlSteerAngle(steering_angle_command);
        const double accel_command = 0.5;
        control_sender.ControlAccel(accel_command);
        const auto end_t = chrono::system_clock::now();
        const auto elapsed_t = chrono::duration<double>(end_t - start_t);
        if (elapsed_t.count() < CANBUS_T) {
            const auto remaining_t = chrono::duration<double>(CANBUS_T) - elapsed_t;
            // cout << "Control thread sleeps for " << remaining_t.count() << " seconds." << endl;
            this_thread::sleep_for(remaining_t);
        } else {
            cout << "Warning: control loop spent " << elapsed_t.count() << " seconds larger than " 
                 << CONTROL_T << " seconds. " << endl;
        }
    }

    if (!control_sender.CloseSocket()) {
        cout << "Close socket failed" << endl;
        return 1;
    } else {
        cout << "Close socket succuss" << endl;
    }

    return 0;
}