#pragma once
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <tuple>

inline void FindFieldInStr(
        std::string::size_type& start,
        std::string::size_type& length,
        const std::string& str,
        char c)
{
	start = str.find_first_of(c);
	if (start == std::string::npos)
	{
		length = 0;
		return;
	}
	length = 1;
	while ((start + length) != str.length() && str[start + length] == c)
	{
		++length;
	}
}

inline std::pair<int, std::string::size_type> ParseFieldInStr(
        const std::string& str,
        const std::string& format,
        char c,
        bool optional=false)
{
	std::string::size_type start, length;

	FindFieldInStr(start, length, format, c);
	if (start == std::string::npos)
	{
		// the field is not found
		if (optional)
		{
			return std::make_pair(0, 0);
		}
		else
		{
			std::string errormsg("Invalid format: ");
			errormsg += format;
			throw std::invalid_argument(errormsg);
		}
	}
	return std::make_pair(atoi(str.substr(start, length).c_str()), length);
}

struct DateTime
{
	int nanoseconds;
	int seconds;
	int minutes;
	int hours;
	int day;
	int month;
	int year;

	const auto members() const { return std::tie(nanoseconds, seconds, minutes, hours, day, month, year); }
	bool operator==(const DateTime& rhs) const { return members() == rhs.members(); }
	bool operator!=(const DateTime& rhs) const { return members() != rhs.members(); }

	static DateTime FromString(const std::string& dateTimeStr, const std::string& format)
	{
		if (dateTimeStr.length() < format.length())
		{
			throw std::invalid_argument(dateTimeStr);
		}

		std::string::size_type start, length;
		int year = ParseFieldInStr(dateTimeStr, format, 'Y').first;
		int month = ParseFieldInStr(dateTimeStr, format, 'M').first;
		int day = ParseFieldInStr(dateTimeStr, format, 'D').first;
		FindFieldInStr(start, length, format, 'Y');
		if (length == 2)
		{
			if (year > 70)
				year += 1900;
			else
				year += 2000;
		}

		int Hour = ParseFieldInStr(dateTimeStr, format, 'h').first;
		int Minute = ParseFieldInStr(dateTimeStr, format, 'm').first;
		int Second = ParseFieldInStr(dateTimeStr, format, 's').first;
		std::pair<int, std::string::size_type> subsecondPair = ParseFieldInStr(dateTimeStr, format, 'f', true);
		int Nanosecond = 0;
		if (subsecondPair.second > 0)
		{
			Nanosecond = static_cast<int>(subsecondPair.first * pow(10, 9-static_cast<int>(subsecondPair.second)));
		}

		return DateTime{
				Nanosecond,
				Second,
				Minute,
				Hour,
				day,
				month,
				year};
	}
};
