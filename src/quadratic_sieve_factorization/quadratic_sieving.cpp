#include <vector>
#include <cmath>

#include "quadratic_sieving.h"
#include "quadratic_congruences_solving.h"
#include "../utilities.h"

namespace large_prime_numbers
{

std::vector<mpz_class> SieveCandidates(const mpz_class& number,
                                       const std::vector<size_t>& factor_base,
                                       const QuadraticSieveConstantParameters& parameters)
{
  mpz_class n_sqrt;
  mpz_sqrt(n_sqrt.get_mpz_t(), number.get_mpz_t());
  mpz_class k = n_sqrt + 1;

  // Sieve over 2M numbers with $r \in [k; k + 2 * M)$, $f(r) = r^2 \pmod p$
  // Silverman's method, accumulate log(p) to all r = congruence mod p
  auto accumulated_estimations_for_factors = std::vector<long double>(2 * parameters.M);
  for (auto p : factor_base) {
    std::vector<mpz_class> congruences;
    if (p == 2)
      congruences = {number % p};
    else
      congruences = CalculateQuadraticCongruences(number, p);
    for (const mpz_class& congruence : congruences) {
      mpz_class accumulation_start = (k / p) * p + congruence;
      if (accumulation_start < k) {
        accumulation_start = accumulation_start + p;
      }
      mpz_class accumulation_start_idx = (accumulation_start - k);
      for (size_t i = accumulation_start_idx.get_ui(); i < 2 * parameters.M; i += p) {
        accumulated_estimations_for_factors[i] += std::log(p);
      }
    }
  }

  // Calculating required target and threshold for sieving with Silverman's method
  long double number_log = mpz_log(number);
  long double target = (number_log) / 2 + logl(parameters.M);
  long double close_enough_threshold = target - parameters.T * logl(factor_base.back());
  std::vector<mpz_class> sieved_numbers;
  for (size_t i = 0; i < 2 * parameters.M; ++i) {
    if (accumulated_estimations_for_factors[i] >= close_enough_threshold) {
      sieved_numbers.emplace_back(k + i);
    }
  }
  return sieved_numbers;
}

} // namespace large_prime_numbers
