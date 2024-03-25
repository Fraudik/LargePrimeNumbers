#pragma once

#include <gmpxx.h>
#include <cassert>

#include "../primality_status.h"
#include "../random_generator.h"
#include "../utilities.h"
#include "lucas_pseudoprimes.h"

namespace large_prime_numbers
{

PrimalityStatus FermatProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base);
PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base);
PrimalityStatus MillerRabinProbablePrimeTest(const mpz_class& number, const mpz_class& base);
PrimalityStatus BPSWPrimalityTest(const mpz_class& number);
PrimalityStatus EnhancedBPSWPrimalityTest(const mpz_class& number);

} // namespace large_prime_numbers
