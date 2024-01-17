#pragma once

#include <gmpxx.h>
#include <cassert>

#include "primality_status.h"

namespace large_prime_numbers
{

typedef std::mt19937 rng_type;

const int64_t kSelfridgeDefaultMaxD = 100'000;

PrimalityStatus FermatProbablePrimeTestWithCheck(mpz_t number, mpz_t base);
PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(mpz_t number, mpz_t base);
PrimalityStatus MillerRabinProbablePrimeTest(mpz_t number, mpz_t base);

struct LucasTestParameters
{
    int64_t p;
    int64_t q;
    // When calculating parameters for Lucas test,
    //  it is possible to immediately detect that the number is composite or prime
    PrimalityStatus pre_test_status;
};

PrimalityStatus LucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q);
PrimalityStatus StrongLucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q);

LucasTestParameters CalculateSelfridgeParametersForLucasTest(mpz_t number, int64_t max_d);
PrimalityStatus LucasProbablePrimeTestWithSelfridgeParameters(mpz_t number, int64_t max_d);
PrimalityStatus StrongLucasProbablePrimeTestWithSelfridgeParameters(mpz_t number, int64_t max_d);

PrimalityStatus BPSWPrimalityTest(mpz_t number);

}
