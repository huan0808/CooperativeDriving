#pragma once
#include <vector>



class FuzzyPID
{
public:
	FuzzyPID() {}
	FuzzyPID(double kp, double kd, double e_b, double ec_b, double ukp_b, double ukd_b);
	double CalculatePIDOutput(double error);
	void PrintRule();
private:
	double E_B, EC_B, Ukp_B, Ukd_B;
	double E_step, EC_step;
	double KP, KD;
	double Err, LastErr, E_Err;
	std::vector<std::vector<double>> FuzzyRuleKp;
	std::vector<std::vector<int>> KpRuleNo;
	std::vector<std::vector<double>> FuzzyRuleKd;
	std::vector<std::vector<int>> KdRuleNo;
	std::vector<double> E_Range, EC_Range, Ukp_Range, Ukd_Range;
	std::vector<double> FuzzyOutput;

	std::vector<double> CalculateFuzzyOutput();
	std::vector<int> FindRange(const double input, const std::vector<double> &range);
	double To_0_1(double rate);
};

