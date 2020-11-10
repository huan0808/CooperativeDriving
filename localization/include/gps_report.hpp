#include <string>

struct GpsReport{
    std::string FPD_Header = "None";
    std::string FPD_GPSWeek = "None";
    std::string FPD_GPSTime = "None";
    std::string Heading = "None";
    std::string Pitch = "None";
    std::string Roll = "None";
    std::string Lattitude = "None";
    std::string Longitude = "None";
    std::string Altitude = "None";
    std::string Ve = "None";
    std::string Vn = "None";
    std::string Vu = "None";
    std::string Baseline = "None";
    std::string NSV1 = "None";
    std::string NSV2 = "None";
    std::string Status = "None";
    std::string FPD_Cs = "None";
    std::string FPD_CrLf = "None";
};

struct ImuReport{
    std::string IMU_Header = "None";
    std::string IMU_GPSWeek = "None";
    std::string IMU_GPSTime = "None";
    std::string GyroX = "None";
    std::string GyroY = "None";
    std::string GyroZ = "None";
    std::string AccX = "None";
    std::string AccY = "None";
    std::string AccZ = "None";
    std::string Tpr = "None";
    std::string IMU_Cs = "None";
    std::string IMU_CrLf = "None";

};