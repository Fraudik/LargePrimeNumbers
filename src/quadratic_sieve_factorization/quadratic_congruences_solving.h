#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

std::vector<mpz_class> CalculateQuadraticCongruences(const mpz_class& quadratic_residue, const mpz_class& odd_prime);

} // namespace large_prime_numbers
