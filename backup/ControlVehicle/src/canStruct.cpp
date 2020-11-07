#include <canStruct.hpp>
#include <iostream>

using namespace std;
void SteeringControl::control()
{
    if(SC_SteeringControlRequest == 0)
    {
        cout << "current is no request" << endl; 
    }
    else if(SC_SteeringControlRequest == 1)
    {
        
    }
    else if(SC_SteeringControlRequest == 2)
    {

    }
}



void SteeringControl::SetThreshold()
{

}