#include "gps_read.hpp"
#include "localization/gps.h"


int main(int argc ,char **argv){
    using namespace std;
    ros::init(argc,argv,"Gps");
    GpsReader gps_read;

    thread read_t(&GpsReader::StartReadGps, &gps_read);
    thread pub_t(&GpsReader::PublishToRos, &gps_read);

    read_t.join();
    pub_t.join();

    return 0;
}

