#include "FuzzyPID.h"
#include <iostream>

FuzzyPID::FuzzyPID(double kp, double kd, double e_b, double ec_b, double ukp_b, double ukd_b)
{
	E_B = e_b;
	EC_B = ec_b;
	Ukp_B = ukp_b;
	Ukd_B = ukd_b;
	KD = kd;
	KP = kp;

	Err = 0.0;
	LastErr = 0.0;
	E_Err = 0.0;

	FuzzyRuleKp = std::vector<std::vector<double>>(7, std::vector<double>(7));
	FuzzyRuleKd = std::vector<std::vector<double>>(7, std::vector<double>(7));

	E_step = E_B / 3.0, EC_step = EC_B / 3.0;

	// calculate the Theory of domain
	for (int i = 0; i < 7; ++i)
	{
		E_Range.push_back((i - 3.0)*E_step);
		EC_Range.push_back((i - 3.0)*EC_step);
		Ukp_Range.push_back((i - 3.0)*(Ukp_B / 3.0));
		Ukd_Range.push_back((i - 3.0)*(Ukd_B / 3.0));
	}

	// the fuzzy rule from experence
	KpRuleNo = std::vector<std::vector<int>>{
			{6,5,5,4,4,3,2},
			{5,5,4,4,3,2,1},
			{4,4,4,4,2,1,0},
			{3,3,3,3,3,3,3},
			{0,1,2,4,4,4,4},
			{1,2,3,4,4,5,5},
			{2,3,4,4,5,5,6}
	};
	KdRuleNo = std::vector<std::vector<int>>{
			{6,5,4,3,4,5,6},
			{5,4,3,2,3,4,5},
			{4,3,2,1,2,3,4},
			{3,2,1,0,1,2,3},
			{4,3,2,1,2,3,4},
			{5,4,3,2,3,4,5},
			{6,5,4,3,4,5,6}
	};

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			FuzzyRuleKp[i][j] = Ukp_Range[KpRuleNo[i][j]];
			FuzzyRuleKd[i][j] = Ukd_Range[KdRuleNo[i][j]];
		}
	}
}

double FuzzyPID::CalculatePIDOutput(double error)
{
	LastErr = Err;
	Err = error;
	E_Err = Err - LastErr;
	std::vector<double> Uk = CalculateFuzzyOutput();
	//std::cout << "Ukp: " << Uk[0] << " Ukd: " << Uk[1] << std::endl;
	double now_kp = KP + Uk[0];
	double now_kd = KD + Uk[1];
	double output = now_kp * Err + now_kd * E_Err;
	//std::cout << "now_kp: " << now_kp << " now_kd: " << now_kd << " E_Err: " << E_Err << std::endl;
	//std::cout << "KP: " << KP << " Err: " << Err << " output: " << Uk[0] << "  " << Uk[1] << std::endl;
	return output;
}

// The error and the differential of the error need to be limited before calling this function
// Otherwise you might not be able to find the right values in your domain
std::vector<double> FuzzyPID::CalculateFuzzyOutput()
{
	// find the domains of Err and E_Err
	std::vector<int> E_Now_Range = FindRange(Err, E_Range);
	std::vector<int> EC_Now_Range = FindRange(E_Err, EC_Range);
	//std::cout << "E_Now_Range " << E_Now_Range[0] << "  " << E_Now_Range[1] << std::endl;

	// calculate the fuzzy output according the domain and Rule
	// centriod defuzzify
	// find the domain first
	double E_Left_Rate = (E_Range[E_Now_Range[1]] - Err) / E_step;
	double E_Right_Rate = (Err - E_Range[E_Now_Range[0]]) / E_step;
	double EC_Left_Rate = (EC_Range[EC_Now_Range[1]] - E_Err) / EC_step;
	double EC_Right_Rate = (E_Err - EC_Range[EC_Now_Range[0]]) / EC_step;
	E_Left_Rate = To_0_1(E_Left_Rate), E_Right_Rate = To_0_1(E_Right_Rate), EC_Left_Rate = To_0_1(EC_Left_Rate), EC_Right_Rate = To_0_1(EC_Right_Rate);
	//std::cout << "E_Left_Rate " << E_Left_Rate << " E_Right_Rate  " << E_Right_Rate << std::endl;
	//std::cout << "EC_Left_Rate " << EC_Left_Rate << " EC_Right_Rate  " << EC_Right_Rate << std::endl;

	// centriod defuzzify
	double Ukp = E_Left_Rate * EC_Left_Rate * FuzzyRuleKp[E_Now_Range[0]][EC_Now_Range[0]] +
		E_Left_Rate * EC_Right_Rate*FuzzyRuleKp[E_Now_Range[0]][EC_Now_Range[1]] +
		E_Right_Rate * EC_Left_Rate*FuzzyRuleKp[E_Now_Range[1]][EC_Now_Range[0]] +
		E_Right_Rate * EC_Right_Rate*FuzzyRuleKp[E_Now_Range[1]][EC_Now_Range[1]];

	double Ukd = E_Left_Rate * EC_Left_Rate*FuzzyRuleKd[E_Now_Range[0]][EC_Now_Range[0]] +
		E_Left_Rate * EC_Right_Rate*FuzzyRuleKd[E_Now_Range[0]][EC_Now_Range[1]] +
		E_Right_Rate * EC_Left_Rate*FuzzyRuleKd[E_Now_Range[1]][EC_Now_Range[0]] +
		E_Right_Rate * EC_Right_Rate*FuzzyRuleKd[E_Now_Range[1]][EC_Now_Range[1]];
	//std::cout << " the inside Ukp/d:  "<< Ukd << " " << Ukp << std::endl;
	//std::vector<double> vec{ Ukp, Ukd };
	//std::cout << "vec: " << vec[0] << " " << vec[1] << std::endl;
	return std::vector<double>{Ukp, Ukd};
}

std::vector<int> FuzzyPID::FindRange(const double input, const std::vector<double>& range)
{
	int Left, Right;
	for (int i = 1; i < 7; ++i)
	{
		// get the number
		Left = i - 1, Right = i;
		if (input < range[i] || i == 6)
			break;
	}
	//std::cout << "Left " << Left << " Right  " << Right << std::endl;
	return std::vector<int>{Left, Right};
}

void FuzzyPID::PrintRule()
{
	std::cout << "KpRuleNo[i][j]" << std::endl;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			std::cout << KpRuleNo[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "E_Range[i]" << std::endl;
	for (int i = 0; i < 7; ++i)
	{
		std::cout << E_Range[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Ukp_Range[i]" << std::endl;
	for (int i = 0; i < 7; ++i)
	{
		std::cout << Ukp_Range[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "FuzzyRuleKp[i][j]" << std::endl;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			std::cout << FuzzyRuleKp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

double FuzzyPID::To_0_1(double rate)
{
	if (rate > 1)
		return 1;
	else if (rate < 0)
		return 0;
	return rate;
}