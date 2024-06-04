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

template <class... Args>
void LucasVTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, LucasVTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasVTestBenchmark(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasVTestWithCheck, std::move(args)...);
}

template <class... Args>
void StrongLucasTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, StrongLucasTestWithCheck, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(LucasTestBenchmark)
BenchmarkOnFourLargestPrimes(LucasVTestBenchmark)
BenchmarkOnFourLargestPrimes(LucasVTestBenchmark)
BenchmarkOnFourLargestPrimes(AcceleratedLucasVTestBenchmark)
BenchmarkOnFourLargestPrimes(StrongLucasTestBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
