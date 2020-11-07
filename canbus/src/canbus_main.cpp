#include <chrono>
#include <iostream>
#include <thread>

#include "canbus_reader.hpp"
#include "chassis_report.hpp"
#include "steering_report.hpp"

#define CANBUS_T 0.01 // in seconds

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
        int ReadFlag = canbus_reader.ReadCanBus(&str_report, &chas_report);
        if (ReadFlag == 2) {
            cout << "Read canbus failed!" << endl;
            //TODO: break?
        }
        else if (ReadFlag == 1){
            continue;
        }
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
        return 1;
    } else {
        cout << "Close socket succuss" << endl;
    }

    return 0;
}