#include <vector>
#include <cmath>
#include <gmpxx.h>
#include <gtest/gtest.h>

#include <primality_status.h>
#include "deterministic_tests/deterministic_primality_tests.h"

namespace large_prime_numbers
{

TEST(MersenneLowPrimes, LucasLehmerTest)
{
  const std::vector<uint> mersenne_low_primes_powers{2, 3, 5, 7, 13, 17, 19, 31};
  for (const uint& power_of_two : mersenne_low_primes_powers)
  {
    uint mersenne_prime = static_cast<uint>(std::pow(2, power_of_two)) - 1;
    EXPECT_TRUE(
        LucasLehmerPrimalityTestWrapperWithCheck(static_cast<mpz_class>(mersenne_prime)) == PrimalityStatus::Prime
        ) << "LucasLehmerTest marked " << mersenne_prime << " as not prime";
  }
}

} // namespace large_prime_numbers
