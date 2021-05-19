#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "control_sender.hpp"



int main(int argc ,char ** argv)
{
    using namespace std;
    cout << " ========= Starting Control Module =========== " << endl;
    ros::init(argc,argv,"control");

    ControlSender control_sender;

    thread receive_t(&ControlSender::StartReceive,&control_sender);
    thread write_t(&ControlSender::StartWrite,&control_sender);
  
    receive_t.join();
    write_t.join();
  
    return 0;
}
