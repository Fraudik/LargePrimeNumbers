#include <gmpxx.h>
#include <optional>
#include <benchmark/benchmark.h>

#include "quadratic_sieve_factorization/quadratic_sieve.h"

namespace large_prime_numbers
{
namespace
{

template<class... Args>
void QuadraticSieveBenchmark(benchmark::State& state, Args&&... args) {
  auto config = QuadraticSieveConstantParameters{4000, 100000000, 3.0};
  auto args_tuple = std::make_tuple(std::move(args)...);
  mpz_class prime{std::get<0>(args_tuple), 10};
  for (auto _ : state) {
    benchmark::DoNotOptimize(TryToGetFactorWithQuadraticSieve(prime, config));
  }
}

}

// 2832282135843641284379 * 4443534478423724553557 = 12585343323244807147760102649942745852986103
BENCHMARK_CAPTURE(QuadraticSieveBenchmark, big_composite, "12585343323244807147760102649942745852986103")->Unit(benchmark::kSecond);
}

BENCHMARK_MAIN()
