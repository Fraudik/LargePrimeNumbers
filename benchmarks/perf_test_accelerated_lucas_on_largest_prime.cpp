#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void LucasTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, LucasTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, AcceleratedLucasTestWithCheck, std::move(args)...);
}

}

BenchmarkOnLargestPrime(LucasTestBenchmark)
BenchmarkOnLargestPrime(AcceleratedLucasTestBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
