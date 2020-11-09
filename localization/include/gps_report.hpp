#include <string>

struct GpsReport{
    using std::string;
    string FPD_Header;
    string FPD_GPSWeek;
    string FPD_GPSTime;
    string Heading;
    string Pitch;
    string Roll;
    string Lattitude;
    string Longitude;
    string Altitude;
    string Ve;
    string Vn;
    string Vu;
    string Baseline;
    string NSV1;
    string NSV2;
    string Status;
    string FPD_Cs;
    string FPD_CrLf;
};