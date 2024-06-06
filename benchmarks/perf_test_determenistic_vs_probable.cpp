#include <gmpxx.h>
#include <iostream>
#include <benchmark/benchmark.h>

#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "deterministic_tests/deterministic_primality_tests.h"
#include "benchmarks_utility.h"

namespace large_prime_numbers
{
namespace
{

template<class... Args>
void TrialDivisionToSqrtBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, TrialDivisionToSqrtPrimalityTest, std::move(args)...);
}

template <class ...Args>
void EnhancedBPSWPrimalityTestBenchmark(benchmark::State& state, Args&&... args) {
  BenchmarkFunction(state, EnhancedBPSWPrimalityTest, std::move(args)...);
}

}

BENCHMARK_CAPTURE(TrialDivisionToSqrtBenchmark, prime_1, "6700417")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrtBenchmark, prime_2, "2147483647")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrtBenchmark, prime_3, "9999990000001")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(TrialDivisionToSqrtBenchmark, prime_4, "67280421310721")->Iterations(100)->Unit(benchmark::kMillisecond);

BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTestBenchmark, prime_1, "6700417")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTestBenchmark, prime_2, "2147483647")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTestBenchmark, prime_3, "999999000001")->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(EnhancedBPSWPrimalityTestBenchmark, prime_4, "67280421310721")->Iterations(100)->Unit(benchmark::kMillisecond);

} // namespace large_prime_numbers


BENCHMARK_MAIN()
