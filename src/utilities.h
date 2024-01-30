#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

bool are_coprime(const mpz_class& a, const mpz_class& b);

inline void mod(mpz_class& number, const mpz_class& mod_base) {
    mpz_mod(number.get_mpz_t(), number.get_mpz_t(), mod_base.get_mpz_t());
}

}