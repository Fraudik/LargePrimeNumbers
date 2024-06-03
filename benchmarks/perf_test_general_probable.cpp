#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/probable_primality_tests.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void FermatProbablePrimeTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, FermatProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void EulerJacobiProbablePrimeTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, EulerJacobiProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void MillerRabinProbablePrimeTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, MillerRabinProbablePrimeTestWithCheck, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTest)
BenchmarkOnFourLargestPrimes(EulerJacobiProbablePrimeTest)
BenchmarkOnFourLargestPrimes(MillerRabinProbablePrimeTest)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
