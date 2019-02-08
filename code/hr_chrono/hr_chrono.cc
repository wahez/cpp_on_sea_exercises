#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/median.hpp>

#include <iostream>
#include <vector>
#include <chrono>

#include "tsc_clock.h"

int main(int, char** argv)
{
	TSCClock::Initialise();
	std::vector<uint64_t> samples(std::atoi(argv[1]));

	for (auto& s : samples)
	{
		s = TSCClock::now();
	}

	namespace acc = boost::accumulators;

	using features = acc::stats<
		acc::tag::mean, acc::tag::variance,
		acc::tag::min, acc::tag::max,
		acc::tag::median>;

	acc::accumulator_set<double, features> c;

	for (std::size_t i = 1; i < samples.size(); ++i)
	{
		c(TSCClock::FromCycles(samples[i] - samples[i - 1]).count());
	}

	std::cout << "mean " << acc::mean(c) << "\n"
			  << "stddev " << std::sqrt(acc::variance(c) * samples.size() / double(samples.size() - 1)) << "\n"
			  << "min " << acc::min(c) << "\n"
			  << "median " << acc::median(c) << "\n"
			  << "max " << acc::max(c) << std::endl;

	return 0;
}

