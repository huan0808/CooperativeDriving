#include "ADRC.h"


ADRC::ADRC(double T, double Kp, double Kd, double B, double W)
{
	h = T;
	h0 = T;
	kp = Kp;
	kd = Kd;
	b = B;
	w = W;
	B1 = 3 * W;
	B2 = 3 * pow(w, 2);
	B3 = pow(w, 3);
}

double ADRC::ComputeWithLinearFeedback(double input, double systemOutput)
{
	ZLast = ESO(input, systemOutput);
	VLast = TD(input);
	std::vector<double> e = { VLast[0] - ZLast[0] ,VLast[1] - ZLast[1] };
	u0 = NLFB(e);
	u = u0 - ZLast[2] / b;
	return u;
}

double ADRC::ComputeWithFalFeedback(double input, double systemOutput, double falPa0, double falDa1, double deta)
{
    ZLast = ESO(input, systemOutput);
    VLast = TD(input);
    double error = VLast[0] - ZLast[0];
    double Derror = VLast[1] - ZLast[1];
    u0 = kp * ESO_fal(error, falPa0, deta) + kd * ESO_fal(Derror, falDa1, deta);
    u = u0 - ZLast[2] / b;
    return u;
}

double ADRC::ComputeWithFhanFeedback(double input, double systemOutput, double fhanh, double fhanc, double fhanr)
{
    ZLast = ESO(input, systemOutput);
    VLast = TD(input);
    double error = VLast[0] - ZLast[0];
    double Derror = VLast[1] - ZLast[1];

    double d = fhanr * fhanh;
    double d0 = d * fhanh;
    double y = error + fhanc * Derror * fhanh;
    double a0 = sqrt(d*d + 8 * fhanr * TD_abs(y));

    double a_0 = TD_abs(y) - d0;
    double a_1 = fhanc * Derror + 0.5*(a0 - d)*TD_unit(y);
    double a_2 = fhanc * Derror + y / fhanh;
    double a = TD_switch(a_0, a_1, a_2);

    double b_0 = TD_abs(a) - d;
    double b_1 = fhanr * TD_unit(a);
    double b_2 = fhanr * a / d;
    double fst = -TD_switch(b_0, b_1, b_2);

    return fst;
}


std::vector<double> ADRC::TD(const double & input)
{
	std::vector<double> V_ = V;
	std::vector<double> fst_input = { V_[0] - input, V_[1] };
	V[0] = V_[0] + V_[1] * h;
	V[1] = TD_fst(fst_input)*h + V_[1];
	return V_;
}

double ADRC::TD_fst(const std::vector<double>& input)
{
	double d = r * h0;
	double d0 = d * h0;
	double y = input[0] + input[1] * h0;
	double a0 = sqrt(d*d + 8 * r * TD_abs(y));

	double a_0 = TD_abs(y) - d0;
	double a_1 = input[1] + 0.5*(a0 - d)*TD_unit(y);
	double a_2 = input[1] + y / h0;
	double a = TD_switch(a_0, a_1, a_2);

	double b_0 = TD_abs(a) - d;
	double b_1 = r * TD_unit(a);
	double b_2 = r * a / d;
	double fst = -TD_switch(b_0, b_1, b_2);

	return fst;
}

double ADRC::TD_unit(double input)
{
	if (input > 0)
		input = 1;
	else if (input < 0)
		input = -1;
	return input;
}

double ADRC::TD_abs(double input)
{
	if (input < 0)
		input = -input;
	return input;
}


double ADRC::TD_switch(double condition, double up_output, double down_output)
{
	if (condition > 0)
		return up_output;
	else
		return down_output;
}


double ADRC::NLFB(const std::vector<double>& input)
{
	return input[0] * kp + input[1] * kd;
}


std::vector<double> ADRC::ESO(const double & u, const double & output)
{
	std::vector<double> Z_ = Z;
	double ep = Z_[0] - output;
	Z[0] = Z_[0] + (Z_[1] - ep * B1)*h;
	Z[1] = Z_[1] + (Z_[2] + b * u - B2 * ESO_fal(ep, a1, deta))*h;
	Z[2] = Z_[2] - ESO_fal(ep, a2, deta) * B3 * h;
	return Z_;
}


double ADRC::ESO_fal(const double & ep, const double & alpha, const double & deta)
{
	double y = 0;
	if (TD_abs(ep) > deta)
		y = TD_unit(ep)*pow(TD_abs(ep), alpha);
	else
		y = ep / pow(deta, 1 - alpha);
	return y;
}
