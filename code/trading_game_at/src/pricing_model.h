#pragma once

#include "types.h"

#include <array>

class PricingModel
{
public:
	static Price CalcPrice(std::array<double, 3> parameters, double event0, Price strikePrice);

private:
	static double CalcNormCDF(double x);
};
