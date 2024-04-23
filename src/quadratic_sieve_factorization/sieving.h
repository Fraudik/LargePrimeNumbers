#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

// Launch constants for MPQS
struct QuadraticSieveConstantParameters {
  size_t factor_base_size;
  size_t M;
  double T;
};

std::vector<mpz_class> SieveCandidates(const mpz_class& number,
                                       const std::vector<size_t>& factor_base,
                                       const QuadraticSieveConstantParameters& parameters);

} // namespace large_prime_numbers
