#include <chrono>
#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "primality_tests_wrapper.h"

namespace large_prime_numbers
{

class LowPrimesList : public testing::Test
{
protected:
    LowPrimesList()
    {
        std::ifstream low_primes_file("primes_2_to_99991.txt", std::ifstream::in);
        assert(low_primes_file);
        int64_t prime;
        while (low_primes_file >> prime)
            low_primes_.push_back(prime);
        low_primes_file.close();
    }

    std::vector<int64_t> low_primes_;
};

template <class PrimalityTest, class... TestSpecificArgs>
void CheckOnListOfPrimes(const std::string& test_name, const std::vector<int64_t>& list_of_primes,
                         PrimalityTest primality_test, TestSpecificArgs&&... args)
{
    bool check_result;
    for (mpz_class checked_prime : list_of_primes)
    {
        check_result = PrimalityTestWrapper(checked_prime.get_mpz_t(), primality_test, std::forward<TestSpecificArgs>(args)...);
        if (!check_result)
        {
            EXPECT_TRUE(check_result) << test_name + " marked " << checked_prime << " as not prime";
        }
    }
}

TEST_F(LowPrimesList, FermatProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("FermatProbablePrimeTestWithBaseTwo",
                        low_primes_,
                        FermatProbablePrimeTestWithCheck, base_for_test.get_mpz_t());
}

TEST_F(LowPrimesList, MillerRabinProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("MillerRabinProbablePrimeTestWithBaseTwo",
                        low_primes_,
                        MillerRabinProbablePrimeTest, base_for_test.get_mpz_t());
}

TEST_F(LowPrimesList, EulerJacobiProbablePrimeTestWithBaseTwo)
{
    mpz_class base_for_test(2);
    CheckOnListOfPrimes("EulerJacobiProbablePrimeTest",
                        low_primes_,
                        EulerJacobiProbablePrimeTestWithCheck, base_for_test.get_mpz_t());
}

TEST_F(LowPrimesList, LucasProbablePrimeTest)
{
    CheckOnListOfPrimes("LucasProbablePrimeTest",
                        low_primes_,
                        LucasProbablePrimeTestWithCheck, 4, 2);
}

TEST_F(LowPrimesList, StrongLucasProbablePrimeTest)
{
    CheckOnListOfPrimes("StrongLucasProbablePrimeTest",
                        low_primes_,
                        StrongLucasProbablePrimeTestWithCheck, 4, 2);
}

TEST_F(LowPrimesList, LucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfPrimes("LucasProbablePrimeTestWithSelfridgeParameters",
                        low_primes_,
                        LucasProbablePrimeTestWithSelfridgeParameters, kSelfridgeDefaultMaxD);
}

TEST_F(LowPrimesList, StrongLucasProbablePrimeTestWithSelfridgeParameters)
{
    CheckOnListOfPrimes("StrongLucasProbablePrimeTestWithSelfridgeParameters",
                        low_primes_,
                        StrongLucasProbablePrimeTestWithSelfridgeParameters, kSelfridgeDefaultMaxD);
}

TEST_F(LowPrimesList, BPSWPrimalityTest)
{
    CheckOnListOfPrimes("BPSWPrimalityTest",
                        low_primes_,
                        BPSWPrimalityTest);
}


}
