#pragma once

#include <experimental/string_view>

inline double FastAtof(std::experimental::string_view sv)
{
	double di = .0;
	std::size_t i = 0;
	for (; i < sv.size() && sv[i] != '.'; ++i)
	{
		di = di * 10.0 + (sv[i] - '0');
	}
	double frac = .0;
	double div = 10.;
	for (++i; i < sv.size(); ++i)
	{
		frac = frac + (sv[i] - '0') / div;
		div *= 10.;
	}
	return frac + di;
}

template <typename ValueT>
ValueT ConsumeValue(std::experimental::string_view);

template <>
inline double ConsumeValue(std::experimental::string_view str)
{
	return FastAtof(str);
}

template <>
inline long ConsumeValue(std::experimental::string_view str)
{
	char *unused;
	return std::strtol(str.data(), &unused, 10);
}

template <>
inline std::experimental::string_view ConsumeValue(std::experimental::string_view str)
{
	return str;
}

template <typename ValueT, std::size_t N>
inline ValueT ConsumeField(std::experimental::string_view str,
						   const char(&name)[N],
						   std::size_t& pos)
{
	const std::size_t start = str.find(name, pos) + N - 1;
	for (pos = start; pos < str.size() && str[pos] != '|'; ++pos);

	const auto value = str.substr(start, pos - start);
	return ConsumeValue<ValueT>(value);
}

