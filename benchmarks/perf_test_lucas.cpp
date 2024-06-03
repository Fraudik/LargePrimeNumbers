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

template <class... Args>
void LucasVTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, LucasVTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasVTest(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasVTestWithCheck, std::move(args)...);
}

template <class... Args>
void StrongLucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, StrongLucasTestWithCheck, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(LucasTest)
BenchmarkOnFourLargestPrimes(AcceleratedLucasTest)
BenchmarkOnFourLargestPrimes(LucasVTest)
BenchmarkOnFourLargestPrimes(AcceleratedLucasVTest)
BenchmarkOnFourLargestPrimes(StrongLucasTest)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
