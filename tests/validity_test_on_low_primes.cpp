#include <gtest/gtest.h>

#include "low_primes_checker.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "deterministic_tests/deterministic_primality_tests.h"

namespace large_prime_numbers
{

TEST(LowPrimes, FermatProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("FermatProbablePrimeTestWithBaseTwo", FermatProbablePrimeTestWithCheck, base_for_test);
}

TEST(LowPrimes, MillerRabinProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("MillerRabinProbablePrimeTestWithBaseTwo", MillerRabinProbablePrimeTestWithCheck, base_for_test);
}

TEST(LowPrimes, EulerJacobiProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("EulerJacobiProbablePrimeTest", EulerJacobiProbablePrimeTestWithCheck, base_for_test);
}

TEST(LowPrimes, LucasTest)
{
    CheckOnListOfLowPrimes("LucasTest", LucasTestWithCheck, 4, 2);
}

TEST(LowPrimes, LucasVTest)
{
    CheckOnListOfLowPrimes("LucasTest", LucasVTestWithCheck, 4, 2);
}

TEST(LowPrimes, AcceleratedLucasTest)
{
    CheckOnListOfLowPrimes("AcceleratedLucasTest", AcceleratedLucasTestWithCheck, 4, 2);
}

TEST(LowPrimes, AcceleratedLucasVTest)
{
    CheckOnListOfLowPrimes("AcceleratedLucasVTest", AcceleratedLucasVTestWithCheck, 4, 2);
}

TEST(LowPrimes, StrongLucasTest)
{
    CheckOnListOfLowPrimes("StrongLucasTest", StrongLucasTestWithCheck, 4, 2);
}

TEST(LowPrimes, LucasTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes("LucasTestWithSelfridgeParameters",
                            LucasTestWithSelfridgeParameters);
}

TEST(LowPrimes, AcceleratedLucasTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes("AcceleratedLucasTestWithSelfridgeParameters",
                           AcceleratedLucasTestWithSelfridgeParameters);
}

TEST(LowPrimes, StrongLucasTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes("StrongLucasTestWithSelfridgeParameters",
                            StrongLucasTestWithSelfridgeParameters);
}

TEST(LowPrimes, BPSWPrimalityTest)
{
    CheckOnListOfLowPrimes("BPSWPrimalityTest", BPSWPrimalityTest);
}

TEST(LowPrimes, EnhancedBPSWPrimalityTest)
{
    CheckOnListOfLowPrimes("EnhancedBPSWPrimalityTest", EnhancedBPSWPrimalityTest);
}

TEST(LowPrimes, TrialDivisionToSqrtPrimalityTest)
{
    CheckOnListOfLowPrimes("TrialDivisionToSqrtPrimalityTest", TrialDivisionToSqrtPrimalityTest);
}

} // namespace large_prime_numbers
