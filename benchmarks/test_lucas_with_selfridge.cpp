#include <gmpxx.h>
#include <iostream>
#include <benchmark/benchmark.h>

#include "quadratic_sieve_factorization/quadratic_sieve.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void LucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, LucasTestWithCheck, std::move(args)...);
}

template <class ...Args>
void LucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, LucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTest(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, AcceleratedLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void StrongLucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, StrongLucasTestWithCheck, std::move(args)...);
}

template <class... Args>
void StrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, StrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, EnhancedStrongLucasTestWithCheck, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(LucasTest)
BenchmarkOnFourLargestPrimes(LucasTestWithSelfridgeParameters)
BenchmarkOnFourLargestPrimes(AcceleratedLucasTest)
BenchmarkOnFourLargestPrimes(AcceleratedLucasTestWithSelfridgeParameters)
BenchmarkOnFourLargestPrimes(StrongLucasTest)
BenchmarkOnFourLargestPrimes(StrongLucasTestWithSelfridgeParameters)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTest)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestWithSelfridgeParameters)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
