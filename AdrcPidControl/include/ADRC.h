#pragma once
#include <vector>
#include <math.h>

class ADRC
{
public:
	ADRC() {}
	ADRC(double T, double Kp, double Kd, double B, double W);
	double ComputeWithLinearFeedback(double input, double systemOutput);
	double ComputeWithFalFeedback(double input, double systemOutput, double falPa0, double falDa1, double theta);
        double ComputeWithFhanFeedback(double input, double systemOutput, double fhanh, double fhanc, double fhanr);

public:
	// initial parameter
	double r = 1000;
	double h, h0;  // h is equal to loop time
	double kp, kd; // similar to PID
	double b; // the feedback of interfere
	double w;
	double B1, B2, B3; // parameters of ESO
	double a1 = 0.5, a2 = 0.25;
	double deta = 0.01;

	// The intermediate results and output are inited 0

	// TD
	std::vector<double> VLast = { 0,0 }; // last time's output
	std::vector<double> V = { 0,0 }; // this time's output

	// nonlinear function
	double u0 = 0, u = 0; // u is the calculated output

	// ESO
	std::vector<double> ZLast = { 0, 0, 0 }; // last time's observered output
	std::vector<double> Z = { 0, 0, 0 };

	// member function
	std::vector<double> TD(const double &input);
	double TD_fst(const std::vector<double> &input);
	double TD_unit(double input);
	double TD_abs(double input);
	double TD_switch(double condition, double up_output, double down_output);

	double NLFB(const std::vector<double> &inout);
//    double Fhan(const double &input);

	std::vector<double> ESO(const double &u, const double &output); // output is the car's actual output
	double ESO_fal(const double &ep, const double &a1pha, const double &deta);

};

