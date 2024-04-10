#pragma once

#include <gmpxx.h>
#include <cmath>

namespace large_prime_numbers
{

// members of decomposition: $2^power_of_two \cdot odd_multiplier$
struct TwoPowersDecomposition {
    mpz_class odd_multiplier;
    uint64_t power_of_two;
};

bool are_coprime(const mpz_class& a, const mpz_class& b);

TwoPowersDecomposition decompose_in_powers_of_two(const mpz_class& a);

inline double mpz_log(const mpz_class& number) {
    signed long int exponent;
    const double multiplier = mpz_get_d_2exp(&exponent, number.get_mpz_t());
    return std::log(multiplier) + std::log(2) * static_cast<double>(exponent);
}

inline void mod(mpz_class& number, const mpz_class& mod_base) {
    mpz_mod(number.get_mpz_t(), number.get_mpz_t(), mod_base.get_mpz_t());
}

} // namespace large_prime_numbers
