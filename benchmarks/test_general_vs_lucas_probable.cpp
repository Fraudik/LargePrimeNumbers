#include <gmpxx.h>
#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void FermatProbablePrimeTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithTwoBasesWithOneBase(state, FermatProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasVTest(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasVTestWithCheck, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParameters(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTest)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestWithSelfridgeParameters)
BenchmarkOnFourLargestPrimes(AcceleratedLucasVTest)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
