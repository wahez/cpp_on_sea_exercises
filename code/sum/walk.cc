#include <random>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>
#include <iostream>

template <class C>
C Gen(std::size_t elements)
{
	std::mt19937 rng{std::random_device()()};
	std::uniform_int_distribution<uint32_t> dist;

	C c(elements);
	std::generate(std::begin(c), std::end(c), [&]() { return dist(rng); });
	return c;
}

int main()
{
	auto c = Gen<std::vector<uint32_t>>(4*1024);
	const auto s = std::accumulate(c.cbegin(), c.cend(), uint32_t{0});
	std::cout << s << std::endl;

	return 0;
}

