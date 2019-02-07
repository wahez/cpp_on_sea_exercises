#include "date_time.h"
#include <sstream>
#include <iomanip>
#include <random>

inline std::string format(const DateTime& dt)
{
	std::ostringstream os;
	os << dt.year << '-'
	   << std::setfill('0') << std::setw(2) << dt.month << '-'
	   << std::setw(2) << dt.day << ' '
	   << std::setw(2) << dt.hours << ':'
	   << std::setw(2) << dt.minutes << ':'
	   << std::setw(2) << dt.seconds << '.'
	   << std::setw(4) << dt.nanoseconds/100000;
	return os.str();
}

inline auto GetDateTimeStrings()
{
	std::vector<std::string> dateTimeStrings;
	std::vector<DateTime> dateTimes;
	DateTime dt{0,0,0,0,1,1,2019};
	for (auto i = 0; i < 10000; ++i)
	{
		dateTimes.push_back(dt);
		dateTimeStrings.push_back(format(dt));
		dt.nanoseconds += 1123'400'000;
		dt.hours += 13;

		dt.seconds += dt.nanoseconds / 1000'000'000; dt.nanoseconds %= 1000'000'000;
		dt.minutes += dt.seconds / 60; dt.seconds %= 60;
		dt.hours += dt.minutes / 60; dt.minutes %= 60;
		dt.day += dt.hours / 24; dt.hours %= 24;
		dt.month += (dt.day-1) / 28; dt.day = (dt.day-1) % 28 + 1;
		dt.year += (dt.month-1) / 12; dt.month = (dt.month-1) % 12 + 1;
	}
	return std::make_pair(dateTimes, dateTimeStrings);
}
