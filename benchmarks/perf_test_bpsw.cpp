#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/probable_primality_tests.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void BPSWPrimalityTestBenchmark(benchmark::State& state, Args&&... args) {
    BenchmarkFunction(state, large_prime_numbers::BPSWPrimalityTest, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTestBenchmark(benchmark::State& state, Args&&... args) {
    BenchmarkFunction(state, large_prime_numbers::EnhancedBPSWPrimalityTest, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, EnhancedStrongLucasTestWithCheck, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(BPSWPrimalityTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedBPSWPrimalityTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestWithSelfridgeParametersBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
