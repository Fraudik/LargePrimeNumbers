#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include <cassert>
#include <gmpxx.h>

namespace large_prime_numbers
{

// members of decomposition: $2^power_of_two \cdot odd_multiplier$
struct TwoPowersDecomposition
{
    mpz_class odd_multiplier;
    uint64_t power_of_two;
};

bool are_coprime(const mpz_class& a, const mpz_class& b);

TwoPowersDecomposition decompose_in_powers_of_two(const mpz_class& a);

// Custom implementation of log function for mpz_class. Inspired by gmp R package, based on mpz_get_d_2exp,
// number = multiplier * 2 ^ exponent  ==> log(a) = log(multiplier) + exponent * log(2)
inline double mpz_log(const mpz_class& number)
{
    signed long int exponent;
    const double multiplier = mpz_get_d_2exp(&exponent, number.get_mpz_t());
    return std::log(multiplier) + std::log(2) * static_cast<double>(exponent);
}

inline void mod(mpz_class& number, const mpz_class& mod_base)
{
    mpz_mod(number.get_mpz_t(), number.get_mpz_t(), mod_base.get_mpz_t());
}

class FileReader
{
 public:
  explicit FileReader(const std::string& path_to_file)
  {
    file.open(path_to_file, std::ifstream::in);
  }

  bool IsOpen() {
    return file.is_open();
  }

  template<typename T>
  friend void operator>>(FileReader& file_reader, std::vector<T>& vec)
  {
    size_t numbers_amount_;
    file_reader.file >> numbers_amount_;
    vec.resize(numbers_amount_);
    for (size_t i = 0; i < numbers_amount_; ++i) {
      file_reader.file >> vec[i];
    }
    file_reader.file.close();
  }

  ~FileReader() {
    if (file.is_open()) {
      file.close();
    }
  }

  private:
    std::ifstream file;
};

} // namespace large_prime_numbers
