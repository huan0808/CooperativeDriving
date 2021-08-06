#pragma once

#define UNSET_DOUBLE -99.99
#define UNSET_INT -99


struct MoveableTarget {
    double long_v  = UNSET_DOUBLE;
    double lat_v = UNSET_DOUBLE;
    double long_dis = UNSET_DOUBLE;
    double lat_dis = UNSET_DOUBLE;
};

struct StationTarget {
    double long_dis = UNSET_DOUBLE;
    double lat_dis = UNSET_DOUBLE;  
};

