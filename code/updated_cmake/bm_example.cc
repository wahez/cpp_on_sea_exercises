#include <iostream>
#include <vector>

#include "benchmark/benchmark.h"

constexpr auto RangeMultiplier = 2;

struct Rectangle
{
	float width;
	float length;
	float area;
    std::string name;
};

std::vector<Rectangle> GenerateRectangles(int n)
{
	std::vector<Rectangle> rectangles;
	for (int i = 0; i < n; ++i)
		rectangles.push_back({static_cast<float>(i), static_cast<float>(100 - i/100.0), 0, std::to_string(i)});
	return rectangles;
}

void vector_of_rectangles(benchmark::State& state)
{
	auto rectangles = GenerateRectangles(state.range(0));
	std::size_t i = 0;
	for (auto _: state)
	{
		rectangles[i].area = rectangles[i].width * rectangles[i].length;
		++i;
		if (i == rectangles.size())
			i = 0;
	}
	benchmark::DoNotOptimize(rectangles);
}
BENCHMARK(vector_of_rectangles)->RangeMultiplier(RangeMultiplier)->Range(512, 263000);

