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
void AcceleratedLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, AcceleratedLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void StrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, StrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnLargestPrime(AcceleratedLucasTestWithSelfridgeParameters)
BenchmarkOnLargestPrime(StrongLucasTestWithSelfridgeParameters)
BenchmarkOnLargestPrime(EnhancedStrongLucasTestWithSelfridgeParameters)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
