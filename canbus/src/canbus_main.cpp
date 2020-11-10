#include <iostream>
#include <thread>

#include "canbus_reader.hpp"
#include "chassis_report.hpp"
#include "steering_report.hpp"

int main(int argc, char **argv) {

    std::cout << " ========= Starting Canbus Module =========== " << std::endl;
    
    ros::init(argc,argv,"can");

    
    CanBusReader canbus_reader;

    //create a thread read from CANBUS
    std::thread read_t(&CanBusReader::StartRead,&canbus_reader);
    //create a thread publish to CAN_INFO node
    std::thread pub_t(&CanBusReader::PublishToRos,&canbus_reader);

    read_t.join();
    pub_t.join();
    return 0;
}