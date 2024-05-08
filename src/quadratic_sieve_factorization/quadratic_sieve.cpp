#include "quadratic_sieve.h"
#include "dixons_algorithm.h"
#include "../utilities.h"

namespace large_prime_numbers
{

namespace
{

constexpr size_t kMaxKnownPrime = 99991;
constexpr size_t kEstimationCoefficient = 100;

std::vector<size_t> CalculateFactorBase(const mpz_class& number, size_t required_factor_base_size)
{
  std::vector<size_t> factor_base{2};
  factor_base.reserve(required_factor_base_size);

  // recommended factor base size for 66 digits is 4500 -- and 9590'th prime is 99991
  // n'th prime p_n ~ n * log(n) as n tends to infinity
  size_t eratosthenes_sieve_size = std::max(static_cast<size_t>(required_factor_base_size *
        std::llround(mpz_log(required_factor_base_size)) *
        kEstimationCoefficient), kMaxKnownPrime);
  std::vector<bool> eratosthenes_sieve(eratosthenes_sieve_size, true);
  for (size_t i = 3; i < eratosthenes_sieve_size && factor_base.size() < required_factor_base_size; i += 2) {
    if (eratosthenes_sieve[i]) {
      if (mpz_legendre(number.get_mpz_t(), static_cast<mpz_class>(i).get_mpz_t()) == 1) {
        factor_base.push_back(i);
      }
      for (size_t j = i * 2; j < eratosthenes_sieve_size; j += i) {
        eratosthenes_sieve[j] = false;
      }
    }
  }
  return factor_base;
}

}

std::optional<mpz_class> TryToGetFactorWithQuadraticSieve(const mpz_class& number,
                                                  const QuadraticSieveConstantParameters& parameters)
{
  auto factor_base = CalculateFactorBase(number, parameters.factor_base_size);
  auto sieved_candidates = SieveCandidates(number, factor_base, parameters);
  return TryToGetFactorWithDixonAlgorithm(number, sieved_candidates, factor_base);
}

} // namespace large_prime_numbers
