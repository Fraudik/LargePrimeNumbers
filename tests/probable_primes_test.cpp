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
        std::ifstream low_primes_file("primes_5_to_99991.txt", std::ifstream::in);
        assert(low_primes_file);
        int64_t prime;
        while (low_primes_file >> prime)
            low_primes_.push_back(prime);
        low_primes_file.close();
    }

    std::vector<int64_t> low_primes_;
};

TEST_F(LowPrimesList, LucasProbablePrimeTest)
{
    mpz_t checked_prime;
    bool check_result;
    mpz_init(checked_prime);

    for (auto prime : low_primes_)
    {
        mpz_set_si(checked_prime, prime);
        check_result = PrimalityTestWrapper(checked_prime, LucasProbablePrimeTestWithCheck, 4, 2);
        if (!check_result)
        {
            mpz_clear(checked_prime);
            EXPECT_TRUE(check_result) << "LucasProbablePrimeTest marked " << prime << " as not prime";
        }
    }
    mpz_clear(checked_prime);
}

}
