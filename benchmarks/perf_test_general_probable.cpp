#include <iostream>
#include <benchmark/benchmark.h>

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
void EulerJacobiProbablePrimeTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, EulerJacobiProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void MillerRabinProbablePrimeTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, MillerRabinProbablePrimeTestWithCheck, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTestBenchmark)
BenchmarkOnFourLargestPrimes(EulerJacobiProbablePrimeTestBenchmark)
BenchmarkOnFourLargestPrimes(MillerRabinProbablePrimeTestBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
