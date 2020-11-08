#include "gsp_report.hpp"
#include "gps_read.hpp"
#include "localization/gps.h"
#include "ros/ros.h"
#include <signal.h>

#define GPS_HZ 100 

int serial_port = 0;

//caught ctrl^c interrupt
void signal_callback_handler(int signum);

int main(int argc ,char **argv){
    using namespace std;

    //exception handle
    signal(SIGINT, signal_callback_handler);
    ros::init(argc,argv,"Gps");
    ros::NodeHandle n;
    ros::Publisher pub_to_GPSINFO = n.advertise<localization::gps>("GPS_INFO",1000);
    ros::loop_rate(GPS_HZ);

    GpsReader gps_read;
    GpsReport gps_report;
    if(gps_read.InitSerial() == false){
        return 1; 
    }
    else{
        cout <<  "serial init success" << endl;
    }
    serial_port = gps_read.serial_port;

    while(ros::ok()){
        if(gps_read.ReadGps(&gps_report) == 1)
        {
            continue;
        }
        localization::gps msg;

        //TODO
        // init gps msg

        pub_to_GPSINFO.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    if(gps_read.CloseSerial() == false){
        cout << "serial close error" << endl;
        return 1;
    }
    
    return 0;
}

void signal_callback_handler(int signum) {
   std::cout << "Caught signal " << signum << std::endl;
   close(serial_port);
   // Terminate program
   exit(signum);
}