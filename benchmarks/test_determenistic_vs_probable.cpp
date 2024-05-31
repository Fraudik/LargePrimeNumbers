#include <gmpxx.h>
#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "deterministic_tests/deterministic_primality_tests.h"
#include "utility.h"

namespace large_prime_numbers
{
namespace
{

template<class... Args>
void TrialDivisionToSqrt(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, TrialDivisionToSqrtPrimalityTest, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTest(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, large_prime_numbers::EnhancedBPSWPrimalityTest, std::move(args)...);
}

}

BENCHMARK_CAPTURE(TrialDivisionToSqrt, prime_1, 6700417)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrt, prime_2, 2147483647)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrt, prime_3, 999999000001)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrt, prime_4, 67280421310721)->Iterations(100)->Unit(benchmark::kMillisecond);

BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTest, prime_1, 6700417)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTest, prime_2, 2147483647)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTest, prime_3, 999999000001)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTest, prime_4, 67280421310721)->Iterations(100)->Unit(benchmark::kMillisecond);

} // namespace large_prime_numbers


BENCHMARK_MAIN()
