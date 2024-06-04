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
void FermatProbablePrimeTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunctionWithOneBase(state, FermatProbablePrimeTestWithCheck, std::move(args)...);
}

template <class ...Args>
void LucasLehmerPrimalityTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, LucasLehmerPrimalityTestWrapperWithCheck, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedBPSWPrimalityTest, std::move(args)...);
}

}

BenchmarkOnFourLargestPrimes(FermatProbablePrimeTestBenchmark)
BenchmarkOnFourLargestPrimes(LucasLehmerPrimalityTestBenchmark)
BenchmarkOnFourLargestPrimes(EnhancedBPSWPrimalityTestBenchmark)

} // namespace large_prime_numbers

BENCHMARK_MAIN()
