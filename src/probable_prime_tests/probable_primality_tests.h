#pragma once

#include <gmpxx.h>

#include "../primality_status.h"

namespace large_prime_numbers
{

PrimalityStatus FermatProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base);
PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base);
PrimalityStatus MillerRabinProbablePrimeTest(const mpz_class& number, const mpz_class& base);
PrimalityStatus BPSWPrimalityTest(const mpz_class& number);
PrimalityStatus EnhancedBPSWPrimalityTest(const mpz_class& number);

} // namespace large_prime_numbers
