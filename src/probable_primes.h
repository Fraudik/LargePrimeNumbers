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

PrimalityStatus FermatProbablePrimeTestWithCheck(mpz_t number, mpz_t base);
PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(mpz_t number, mpz_t base);
PrimalityStatus MillerRabinProbablePrimeTest(mpz_t number, mpz_t base);

PrimalityStatus LucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q);
PrimalityStatus StrongLucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q);
LucasTestParameters CalculateSelfridgeParametersForLucasTest(mpz_t number, int64_t max_d);
PrimalityStatus BPSWPrimalityTest(mpz_t number);

}
