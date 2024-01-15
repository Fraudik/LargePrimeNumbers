#pragma once

#include <gmpxx.h>
#include <cassert>

#include "primality_status.h"

namespace large_prime_numbers
{

struct LucasTestParameters
{
    int64_t p;
    int64_t q;
    // When calculating parameters for Lucas test,
    //  it is possible to immediately detect that the number is composite or prime
    PrimalityStatus pre_test_status;
};

PrimalityStatus FermatProbablePrimeTestWithCheck(mpz_t a, mpz_t p);
PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(mpz_t a, mpz_t p);
PrimalityStatus MillerRabinProbablePrimeTest(mpz_t a, mpz_t p);

PrimalityStatus LucasProbablePrimeTestWithCheck(mpz_t n, int64_t p, int64_t q);
PrimalityStatus StrongLucasProbablePrimeTestWithCheck(mpz_t n, int64_t p, int64_t q);
LucasTestParameters CalculateSelfridgeParametersForLucasTest(mpz_t n, int64_t max_d);
PrimalityStatus BPSWPrimalityTest(mpz_t n);

}
