#include "gps_read.hpp"
#include "localization/gps.h"


int main(int argc ,char **argv){
    using namespace std;
    cout << " ========= Starting Localization Module =========== " << endl;
    ros::init(argc,argv,"Gps");
    GpsReader gps_read;
    gps_read.StartReadGps_fake();

    return 0;
}

