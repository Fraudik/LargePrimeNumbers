#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

std::optional<mpz_class> GetFactorWithDixonAlgorithm(const mpz_class& number,
                                                     const std::vector<mpz_class>& sieved_entries,
                                                     const std::vector<size_t>& factor_base);

} // namespace large_prime_numbers
