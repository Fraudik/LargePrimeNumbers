#include <gtest/gtest.h>

#include "quadratic_sieve_factorization/multiple_polynomial_quadratic_sieve.h"

namespace large_prime_numbers
{

TEST(MPQS, ThirteenDigitsNumber)
{
   auto kTestParams = large_prime_numbers::QuadraticSieveConstantParameters{100, 5000, 1.5};
   mpz_class number("4999486012441", 10);
   auto found_factor = TryToGetFactorWithQuadraticSieve(number, kTestParams);
   EXPECT_TRUE(found_factor.has_value());
   EXPECT_TRUE(found_factor.value() == 999961 || found_factor.value() == 4999681);
}

TEST(MPQS, TwentyThreeDigitsNumber)
{
   auto kTestParams = large_prime_numbers::QuadraticSieveConstantParameters{200, 100000, 1.5};
   mpz_class composite_number("147573952589676412927", 10);
   auto found_factor = TryToGetFactorWithQuadraticSieve(composite_number, kTestParams);
   EXPECT_TRUE(found_factor.has_value());
   EXPECT_TRUE(found_factor.value() == 193707721 || found_factor.value() == 761838257287);
}

TEST(MPQS, ForytFourDigitsPrime)
{
   auto kTestParams = large_prime_numbers::QuadraticSieveConstantParameters{1200, 100000, 2};
   mpz_class prime("20988936657440586486151264256610222593863921", 10);
   EXPECT_FALSE(TryToGetFactorWithQuadraticSieve(prime, kTestParams).has_value());
}

} // namespace large_prime_numbers
