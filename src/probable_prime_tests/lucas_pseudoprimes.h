#pragma once

#include <cassert>
#include <gmpxx.h>

#include "../primality_status.h"
#include "../utilities.h"

namespace large_prime_numbers
{

PrimalityStatus LucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus AcceleratedLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus StrongLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus EnhancedStrongLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q);

struct SelfridgeParametersForLucasTest
{
    int64_t p;
    int64_t q;
    // When calculating parameters for Lucas test,
    //  it is possible to immediately detect that the number is composite or prime
    PrimalityStatus pre_test_status;
};

struct LucasSequenceMembers
{
    mpz_class U_n;
    mpz_class V_n;
};

SelfridgeParametersForLucasTest CalculateSelfridgeParametersForLucasTest(const mpz_class& number);
PrimalityStatus LucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus AcceleratedLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus StrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus EnhancedStrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number);

} // namespace large_prime_numbers

