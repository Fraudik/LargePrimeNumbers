#pragma once

#include <cassert>
#include <gmpxx.h>

#include "../primality_status.h"
#include "../utilities.h"

namespace large_prime_numbers
{

PrimalityStatus LucasTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus AcceleratedLucasTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus LucasVTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus AcceleratedLucasVTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus StrongLucasTestWithCheck(const mpz_class& number, int64_t p, int64_t q);
PrimalityStatus EnhancedStrongLucasTestWithCheck(const mpz_class& number, int64_t p, int64_t q);

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

SelfridgeParametersForLucasTest CalculateSelfridgeParameters(const mpz_class& number);
PrimalityStatus LucasTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus AcceleratedLucasTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus StrongLucasTestWithSelfridgeParameters(const mpz_class& number);
PrimalityStatus EnhancedStrongLucasTestWithSelfridgeParameters(const mpz_class& number);

} // namespace large_prime_numbers

