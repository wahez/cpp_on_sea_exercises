#include "util.hh"

#include "../v0/dictionary.hh"
#include "../v1/dictionary.hh"
#include "../v2/dictionary.hh"
#include "../v3/dictionary.hh"
#include "../v4/dictionary.hh"

// instrumentation
#include <papipp.h>
#include <valgrind/callgrind.h>

#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>

std::vector<std::string> wordsIn;
std::vector<std::string> wordsNotIn;

template<typename DictType>
void InDictionary(benchmark::State& state)
{
    int idx = 0;
    DictType dict(wordsIn);
    bool allFound = true;

    for(auto _ : state)
    {
        const std::string& word = wordsIn[idx];
        idx = (idx+1) % wordsIn.size();
        benchmark::DoNotOptimize(allFound &= dict.in_dictionary(word));
    }

    if (!allFound)
        std::cout << "InDictionary consistency check failed" << std::endl;
}

template<typename DictType>
void NotInDictionary(benchmark::State& state)
{
    int idx = 0;
    DictType dict(wordsIn);
    bool someFound = false;

    for(auto _ : state)
    {
        const std::string& word = wordsNotIn[idx];
        idx = (idx+1) % wordsNotIn.size();
        benchmark::DoNotOptimize(someFound |= dict.in_dictionary(word));
    }

    if (someFound)
        std::cout << "NotInDictionary consistency check failed" << std::endl;
}

BENCHMARK_TEMPLATE(InDictionary, v0::Dictionary);
BENCHMARK_TEMPLATE(InDictionary, v1::Dictionary);
BENCHMARK_TEMPLATE(InDictionary, v2::Dictionary);
BENCHMARK_TEMPLATE(InDictionary, v3::Dictionary);
BENCHMARK_TEMPLATE(InDictionary, v4::Dictionary);
BENCHMARK_TEMPLATE(NotInDictionary, v0::Dictionary);
BENCHMARK_TEMPLATE(NotInDictionary, v1::Dictionary);
BENCHMARK_TEMPLATE(NotInDictionary, v2::Dictionary);
BENCHMARK_TEMPLATE(NotInDictionary, v3::Dictionary);
BENCHMARK_TEMPLATE(NotInDictionary, v4::Dictionary);

int main(int argc, char** argv)
{
    constexpr int DICT_SIZE = 99171;
    std::vector<std::string> words = CreateUniqueRandomStrings(DICT_SIZE*2);
    wordsIn.assign(words.begin(), words.begin() + DICT_SIZE);
    wordsNotIn.assign(words.begin() + DICT_SIZE, words.end());

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
