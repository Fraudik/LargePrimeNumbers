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
void LucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, LucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTestBenchmark(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, AcceleratedLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void StrongLucasTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, StrongLucasTestWithCheck, std::move(args)...);
}

template <class... Args>
void StrongLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, StrongLucasTestWithSelfridgeParameters, std::move(args)...);
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

BenchmarkOnFourLargestPrimes(LucasTestBenchmark)
BenchmarkOnFourLargestPrimes(LucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnFourLargestPrimes(AcceleratedLucasTestBenchmark)
BenchmarkOnFourLargestPrimes(AcceleratedLucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnFourLargestPrimes(StrongLucasTestBenchmark)
BenchmarkOnFourLargestPrimes(StrongLucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestWithSelfridgeParametersBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
