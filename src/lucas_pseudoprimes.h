#pragma once

#include <gmpxx.h>
#include <cassert>

#include "primality_status.h"
#include "utilities.h"

namespace large_prime_numbers
{

PrimalityStatus LucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus StrongLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);

namespace SelfridgeDetail
{

struct LucasTestParameters
{
    int64_t p;
    int64_t q;
    // When calculating parameters for Lucas test,
    //  it is possible to immediately detect that the number is composite or prime
    PrimalityStatus pre_test_status;
};

constexpr int64_t kSelfridgeDefaultMaxD = 100'000;

}

SelfridgeDetail::LucasTestParameters CalculateSelfridgeParametersForLucasTest(const mpz_class& number, int64_t max_d);
PrimalityStatus LucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);
PrimalityStatus StrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);

}