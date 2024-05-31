#include <gmpxx.h>
#include <iostream>
#include <optional>
#include <benchmark/benchmark.h>

#include "quadratic_sieve_factorization/quadratic_sieve.h"
#include "utility.h"

namespace large_prime_numbers
{
namespace
{

template<class... Args>
void BenchmarkQuadraticSieve(benchmark::State& state, Args&&... args) {
  auto config = large_prime_numbers::QuadraticSieveConstantParameters{4000, 100000000, 3.0};
  auto args_tuple = std::make_tuple(std::move(args)...);
  mpz_class prime{std::get<0>(args_tuple), 10};
  for (auto _ : state) {
    benchmark::DoNotOptimize(large_prime_numbers::TryToGetFactorWithQuadraticSieve(prime, config));
  }
}

}

// 2832282135843641284379 * 4443534478423724553557 = 12585343323244807147760102649942745852986103
BENCHMARK_CAPTURE(BenchmarkQuadraticSieve, big_composite, "12585343323244807147760102649942745852986103")->Unit(benchmark::kSecond);
}

BENCHMARK_MAIN()
