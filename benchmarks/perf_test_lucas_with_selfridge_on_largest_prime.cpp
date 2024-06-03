#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void AcceleratedLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::AcceleratedLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void StrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::StrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnLargestPrime(AcceleratedLucasTestWithSelfridgeParameters)
BenchmarkOnLargestPrime(StrongLucasTestWithSelfridgeParameters)
BenchmarkOnLargestPrime(EnhancedStrongLucasTestWithSelfridgeParameters)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
