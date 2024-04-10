#include <fstream>
#include <iostream>
#include <gtest/gtest.h>

#include "primality_tests_wrapper.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "probable_prime_tests/lucas_pseudoprimes.h"


namespace large_prime_numbers {

namespace {

struct LowPrimes : public testing::Test
{
    LowPrimes()
    {
        std::ifstream low_primes_file("primes_2_to_99991.txt", std::ifstream::in);
        assert(low_primes_file);

        // first line of the file contains the number of primes in it
        int64_t primes_amount;
        low_primes_file >> primes_amount;
        low_primes_.reserve(primes_amount);
        mpz_class prime;
        while (low_primes_file >> prime)
            low_primes_.push_back(prime);
    }

    std::vector<mpz_class> low_primes_;
};



template <class PrimalityTest, class... TestSpecificArgs>
void CheckOnListOfPrimes(
    const std::string& test_name, const std::vector<mpz_class>& list_of_primes, PrimalityTest primality_test, TestSpecificArgs&&... args)
{
    for (const mpz_class& checked_prime : list_of_primes)
    {
        bool is_test_marked_prime = PrimalityTestWrapper(checked_prime,
                                                         primality_test, std::forward<TestSpecificArgs>(args)...);
        EXPECT_TRUE(is_test_marked_prime) << test_name + " marked " << checked_prime << " as not prime";
    }
}

}

TEST_F(LowPrimes, FermatProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("FermatProbablePrimeTestWithBaseTwo", low_primes_, FermatProbablePrimeTestWithCheck, base_for_test);
}

TEST_F(LowPrimes, FermatProbablePrimeTestWithRandomBase)
{
    bool check_result;
    mpz_class a(45427);
    check_result = PrimalityTestWithRandomBaseWrapper(a, FermatProbablePrimeTestWithCheck, std::nullopt);
    if (!check_result)
        EXPECT_TRUE(check_result);
}

TEST_F(LowPrimes, MillerRabinProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("MillerRabinProbablePrimeTestWithBaseTwo", low_primes_, MillerRabinProbablePrimeTest, base_for_test);
}

TEST_F(LowPrimes, EulerJacobiProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("EulerJacobiProbablePrimeTest", low_primes_, EulerJacobiProbablePrimeTestWithCheck, base_for_test);
}

TEST_F(LowPrimes, LucasProbablePrimeTest)
{
    CheckOnListOfPrimes("LucasProbablePrimeTest", low_primes_, LucasProbablePrimeTestWithCheck, 4, 2);
}

TEST_F(LowPrimes, LucasKovalProbablePrimeTest)
{
    CheckOnListOfPrimes("LucasKovalProbablePrimeTest", low_primes_, AcceleratedLucasProbablePrimeTestWithCheck, 4, 2);
}

TEST_F(LowPrimes, StrongLucasProbablePrimeTest)
{
    CheckOnListOfPrimes("StrongLucasProbablePrimeTest", low_primes_, StrongLucasProbablePrimeTestWithCheck, 4, 2);
}

TEST_F(LowPrimes, LucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfPrimes(
        "LucasProbablePrimeTestWithSelfridgeParameters",
        low_primes_,
        LucasProbablePrimeTestWithSelfridgeParameters);
}

TEST_F(LowPrimes, AcceleratedLucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfPrimes(
        "AcceleratedLucasProbablePrimeTestWithSelfridgeParameters",
        low_primes_,
        AcceleratedLucasProbablePrimeTestWithSelfridgeParameters);
}

TEST_F(LowPrimes, StrongLucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfPrimes(
        "StrongLucasProbablePrimeTestWithSelfridgeParameters",
        low_primes_,
        StrongLucasProbablePrimeTestWithSelfridgeParameters);
}

TEST_F(LowPrimes, BPSWPrimalityTest)
{
    CheckOnListOfPrimes("BPSWPrimalityTest", low_primes_, BPSWPrimalityTest);
}

TEST_F(LowPrimes, EnhancedBPSWPrimalityTest)
{
    CheckOnListOfPrimes("EnhancedBPSWPrimalityTest", low_primes_, EnhancedBPSWPrimalityTest);
}

} // namespace large_prime_numbers
