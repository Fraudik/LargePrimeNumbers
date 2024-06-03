#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void LucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, LucasTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, AcceleratedLucasTestWithCheck, std::move(args)...);
}

}

BenchmarkOnLargestPrime(LucasTest)
BenchmarkOnLargestPrime(AcceleratedLucasTest)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
