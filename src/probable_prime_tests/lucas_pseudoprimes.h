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

struct LucasSequenceMembers
{
    mpz_class U_n;
    mpz_class V_n;
};

SelfridgeDetail::LucasTestParameters CalculateSelfridgeParametersForLucasTest(const mpz_class& number, int64_t max_d);
PrimalityStatus LucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);
PrimalityStatus AcceleratedLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);
PrimalityStatus StrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);
PrimalityStatus EnhancedStrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d);

} // namespace large_prime_numbers
