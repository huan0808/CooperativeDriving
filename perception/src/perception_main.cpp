#include <iostream>
#include <thread>

#include "perception_reader.hpp"
//#include "chassis_report.hpp"
//#include "steering_report.hpp"

int main(int argc, char **argv) {

    std::cout << " ========= Starting Perception Module =========== " << std::endl;
    
    ros::init(argc,argv,"perception");

    
    Perception perception_reader;
    
    //create a thread read from CANBUS
    std::thread read_t(&Perception::StartRead,&perception_reader);
    //create a thread publish to CAN_INFO node
    std::thread pub_t(&Perception::PublishToRos,&perception_reader);
   
    read_t.join();
    pub_t.join();

    return 0;
}
