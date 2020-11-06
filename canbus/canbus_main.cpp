#include <chrono>
#include <iostream>
#include <thread>

#include "canbus_reader.hpp"
#include "chassis_report.hpp"
#include "steering_report.hpp"

#define CANBUS_T 1.0 // in seconds

int main(int argc, char **argv) {
    using namespace std;

    cout << " ========= Starting Canbus Module =========== " << endl;
    CanBusReader canbus_reader;
    SteeringReport str_report;
    ChassisReport chas_report;
    if (!canbus_reader.InitSocket()) {
        cout << "Init socket failed" << endl;
        return 1;
    } else {
        cout << "Init socket success" << endl;
    }

    while (true) {
        const auto start_t = chrono::system_clock::now();
        if (!canbus_reader.ReadCanBus(&str_report, &chas_report)) {
            cout << "Read canbus failed!" << endl;
        };
        const auto end_t = chrono::system_clock::now();
        const auto elapsed_t = chrono::duration<double>(end_t - start_t);
        if (elapsed_t.count() < CANBUS_T) {
            const auto remaining_t = chrono::duration<double>(CANBUS_T) - elapsed_t;
            // cout << "Canbus thread sleeps for " << remaining_t.count() << " seconds." << endl;
            this_thread::sleep_for(remaining_t);
        } else {
            cout << "Warning: canbus loop spent " << elapsed_t.count() << " seconds larger than " 
                 << CANBUS_T << " seconds. " << endl;
        }
    }

    if (!canbus_reader.CloseSocket()) {
        cout << "Close socket failed" << endl;
    } else {
        cout << "Close socket succuss" << endl;
    }

    return 0;
}