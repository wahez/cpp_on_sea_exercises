#include "date_time.h"
#include "helpers.h"
#include <benchmark/benchmark.h>

void OldDateTimeParsing(benchmark::State& state)
{
	const auto dateTimes = GetDateTimeStrings();
	std::size_t i = 0;
	while (state.KeepRunning())
	{
		if (dateTimes.first[i] != DateTime::FromString(dateTimes.second[i], "YYYY-MM-DD hh:mm:ss.ffff"))
			throw std::runtime_error("Not the same" + dateTimes.second[i]);
		if (++i == dateTimes.first.size())
			i = 0;
	}
}
BENCHMARK(OldDateTimeParsing);
