#include <iostream>
#include <benchmark/benchmark.h>

#include "deterministic_tests/deterministic_primality_tests.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template <class ...Args>
void FermatProbablePrimeTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, large_prime_numbers::FermatProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void LucasLehmerPrimalityTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, LucasLehmerPrimalityTestWrapperWithCheck, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::EnhancedBPSWPrimalityTest, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTest)
BenchmarkOnFourLargestPrimes(LucasLehmerPrimalityTest)
BenchmarkOnFourLargestPrimes(EnhancedBPSWPrimalityTest)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
