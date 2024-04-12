#include <iostream>
#include <gtest/gtest.h>

#include "primality_tests_wrapper.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"
#include "utilities.h"

namespace large_prime_numbers
{

namespace
{

template <class PrimalityTest, class... TestSpecificArgs>
void CheckOnListOfLowPrimes(const std::string& test_name, PrimalityTest primality_test, TestSpecificArgs&&... args)
{
    FileReader file("primes_2_to_99991.txt");
    EXPECT_TRUE(file.IsOpen()) << "Can not open file with primes";

    std::vector<int64_t> low_primes;
    file >> low_primes;
    for (const mpz_class& prime : low_primes)
    {
        bool is_test_marked_prime = PrimalityTestWrapper(prime,
                                                         primality_test, std::forward<TestSpecificArgs>(args)...);
        EXPECT_TRUE(is_test_marked_prime) << test_name + " marked " << prime << " as not prime";
    }
}

}

TEST(LowPrimes, FermatProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("FermatProbablePrimeTestWithBaseTwo", FermatProbablePrimeTestWithCheck, base_for_test);
}

TEST(LowPrimes, MillerRabinProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("MillerRabinProbablePrimeTestWithBaseTwo", MillerRabinProbablePrimeTest, base_for_test);
}

TEST(LowPrimes, EulerJacobiProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfLowPrimes("EulerJacobiProbablePrimeTest", EulerJacobiProbablePrimeTestWithCheck, base_for_test);
}

TEST(LowPrimes, LucasProbablePrimeTest)
{
    CheckOnListOfLowPrimes("LucasProbablePrimeTest", LucasProbablePrimeTestWithCheck, 4, 2);
}

TEST(LowPrimes, LucasKovalProbablePrimeTest)
{
    CheckOnListOfLowPrimes("LucasKovalProbablePrimeTest", AcceleratedLucasProbablePrimeTestWithCheck, 4, 2);
}

TEST(LowPrimes, StrongLucasProbablePrimeTest)
{
    CheckOnListOfLowPrimes("StrongLucasProbablePrimeTest", StrongLucasProbablePrimeTestWithCheck, 4, 2);
}

TEST(LowPrimes, LucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes( "LucasProbablePrimeTestWithSelfridgeParameters",
                            LucasProbablePrimeTestWithSelfridgeParameters);
}

TEST(LowPrimes, AcceleratedLucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes("AcceleratedLucasProbablePrimeTestWithSelfridgeParameters",
                           AcceleratedLucasProbablePrimeTestWithSelfridgeParameters);
}

TEST(LowPrimes, StrongLucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfLowPrimes( "StrongLucasProbablePrimeTestWithSelfridgeParameters",
                            StrongLucasProbablePrimeTestWithSelfridgeParameters);
}

TEST(LowPrimes, BPSWPrimalityTest)
{
    CheckOnListOfLowPrimes("BPSWPrimalityTest", BPSWPrimalityTest);
}

TEST(LowPrimes, EnhancedBPSWPrimalityTest)
{
    CheckOnListOfLowPrimes("EnhancedBPSWPrimalityTest", EnhancedBPSWPrimalityTest);
}

} // namespace large_prime_numbers
