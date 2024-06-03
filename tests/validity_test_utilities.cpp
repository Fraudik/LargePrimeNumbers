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

TEST(Utilities, decompose_in_powers_of_two)
{
  size_t max_value_to_test = 1000;
  for (size_t number = 1; number < max_value_to_test; ++number) {
    auto decomposition = decompose_in_powers_of_two(number);
    auto value_from_decomposition = std::pow(2, decomposition.power_of_two) * decomposition.odd_multiplier;
    EXPECT_TRUE(value_from_decomposition == number)
    << "decompose_in_powers_of_two error, right value: " << number
    << " is not equal to calculated: " << value_from_decomposition
    << " with decomposition power of tow " << decomposition.power_of_two
    << " and odd_multiplier " << decomposition.odd_multiplier;
  }
}

TEST(Utilities, FileReader)
{
    FileReader file("primes_2_to_99991.txt");
    EXPECT_TRUE(file.IsOpen()) << "Can not open file with primes";
    std::vector<int64_t> low_primes;
    file >> low_primes;
    EXPECT_TRUE(low_primes.size() == 9591);
}

} // namespace large_prime_numbers
