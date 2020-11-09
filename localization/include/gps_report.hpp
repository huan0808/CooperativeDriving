#include <string>

struct GpsReport{
    std::string FPD_Header;
    std::string FPD_GPSWeek;
    std::string FPD_GPSTime;
    std::string Heading;
    std::string Pitch;
    std::string Roll;
    std::string Lattitude;
    std::string Longitude;
    std::string Altitude;
    std::string Ve;
    std::string Vn;
    std::string Vu;
    std::string Baseline;
    std::string NSV1;
    std::string NSV2;
    std::string Status;
    std::string FPD_Cs;
    std::string FPD_CrLf;
};

struct ImuReport{
    std::string IMU_Header;
    std::string IMU_GPSWeek;
    std::string IMU_GPSTime;
    std::string GyroX;
    std::string GyroY;
    std::string GyroZ;
    std::string AccX;
    std::string AccY;
    std::string AccZ;
    std::string Tpr;
    std::string IMU_Cs;
    std::string IMU_CrLf;

};