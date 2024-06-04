#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void AcceleratedLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, AcceleratedLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void StrongLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, StrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnLargestPrime(AcceleratedLucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnLargestPrime(StrongLucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnLargestPrime(EnhancedStrongLucasTestWithSelfridgeParametersBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
