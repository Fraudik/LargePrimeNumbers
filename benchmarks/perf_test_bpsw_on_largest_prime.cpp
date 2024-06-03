#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/probable_primality_tests.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

{
namespace
{

template <class ...Args>
void BPSWPrimalityTest(benchmark::State& state, Args&&... args) {
    BenchmarkFunction(state, large_prime_numbers::BPSWPrimalityTest, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTest(benchmark::State& state, Args&&... args) {
    BenchmarkFunction(state, large_prime_numbers::EnhancedBPSWPrimalityTest, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBases(state, large_prime_numbers::EnhancedStrongLucasTestWithCheck, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnLargestPrime(BPSWPrimalityTest)
BenchmarkOnLargestPrime(EnhancedBPSWPrimalityTest)
BenchmarkOnLargestPrime(EnhancedStrongLucasTest)
BenchmarkOnLargestPrime(EnhancedStrongLucasTestWithSelfridgeParameters)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
