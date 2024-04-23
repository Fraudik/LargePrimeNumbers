#include <cmath>
#include <gtest/gtest.h>

#include "utilities.h"
#include "quadratic_sieve_factorization/quadratic_sieve.h"

namespace large_prime_numbers
{

TEST(Utilities, mpz_log)
{
  double max_estimation_error = 1e-12;
  size_t max_value_to_test = 1e8;
  for (size_t number = 1; number < max_value_to_test; ++number) {
    EXPECT_TRUE(abs(std::log(number) - mpz_log(number)) < max_estimation_error)
    << "mpz_log error, right value: " << std::log(number)
    << " is not equal to calculated: " << mpz_log(number);
  }
}

} // namespace large_prime_numbers
