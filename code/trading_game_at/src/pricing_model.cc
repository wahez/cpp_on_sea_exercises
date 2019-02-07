#include "pricing_model.h"

#define _USE_MATH_DEFINES
#include <cmath>

Price PricingModel::CalcPrice(std::array<double, 3> p, double event0, Price strikePrice)
{
	const double d1 = (std::log(event0 / strikePrice.mValue) + (p[0] + 0.5 * p[1] * p[1]) * p[2]) / (p[1] * std::sqrt(p[2]));
	const double d2 = (std::log(event0 / strikePrice.mValue) + (p[0] - 0.5 * p[1] * p[1]) * p[2]) / (p[1] * std::sqrt(p[2]));

	return Price{event0 * CalcNormCDF(d1) - std::exp(-p[0] * p[2]) * strikePrice.mValue * CalcNormCDF(d2)};
}

double PricingModel::CalcNormCDF(double x)
{
	const double k = 1.0 / (1.0 + 0.2316419 * x);
	const double kSum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

	if (x >= .0)
	{
		return 1.0 - (1.0 / (std::pow(2 * M_PI, 0.5))) * std::exp(-0.5 * x * x) * kSum;
	}

	return 1.0 - CalcNormCDF(-x);
}
