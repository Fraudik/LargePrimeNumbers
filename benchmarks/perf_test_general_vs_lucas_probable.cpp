#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void FermatProbablePrimeTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, FermatProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void AcceleratedLucasVTestBenchmark(benchmark::State& state, Args&&... args) {
    BenchmarkFunctionWithTwoBases(state, AcceleratedLucasVTestWithCheck, std::move(args)...);
}

template <class... Args>
void EnhancedStrongLucasTestWithSelfridgeParametersBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedStrongLucasTestWithSelfridgeParameters, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedStrongLucasTestWithSelfridgeParametersBenchmark)
BenchmarkOnFourLargestPrimes(AcceleratedLucasVTestBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
