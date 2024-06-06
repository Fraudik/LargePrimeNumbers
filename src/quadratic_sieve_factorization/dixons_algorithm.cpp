#include <optional>
#include <cassert>

#include "dixons_algorithm.h"
#include "linalg.h"
#include "../utilities.h"

namespace large_prime_numbers
{

// Fills factor_powers and returns true if $g(r) = r * r \pmod n$ can be fully factorized
bool CanBeFactorizedOverFactorBase(const mpz_class& r,
                                   const mpz_class& n,
                                   const std::vector<size_t>& factor_base,
                                   std::vector<size_t>& factor_powers)
{
  mpz_class g_r = r * r;
  mod(g_r, n);
  assert(g_r > 1);
  for (size_t i = 0; i < factor_base.size(); ++i) {
    while (g_r % factor_base[i] == 0) {
      factor_powers[i]++;
      g_r /= factor_base[i];
      if (g_r == 1)
        return true;
    }
  }
  return false;
}

// Return factored entries and matrix of factor powers for them
std::pair<std::vector<mpz_class>, BitMatrix> FactorizeCandidates(const mpz_class& number,
                                                                 const std::vector<mpz_class>& sieved_entries,
                                                                 const std::vector<size_t>& factor_base)
{
  std::vector<mpz_class> factorized_entries;
  factorized_entries.reserve(factor_base.size());

  BitMatrix matrix(factor_base.size() + 1, std::vector<uint8_t>(2 * factor_base.size() + 1));
  std::vector<size_t> factor_powers(factor_base.size());
  size_t amount_of_factored_entries = 0;
  for (const mpz_class& entry : sieved_entries) {
    std::fill(factor_powers.begin(), factor_powers.end(), 0);
    if (CanBeFactorizedOverFactorBase(entry, number, factor_base, factor_powers)) {
      for (size_t factor_idx = 0; factor_idx < factor_base.size(); factor_idx++) {
        matrix[amount_of_factored_entries][factor_idx] = (factor_powers[factor_idx] % 2 == 0);
      }
      matrix[amount_of_factored_entries][factor_base.size() + amount_of_factored_entries] = true;
      factorized_entries.push_back(entry);
      amount_of_factored_entries++;
    }

    if (factorized_entries.size() == factor_base.size())
      break;
  }
  return {factorized_entries, matrix};
}

std::optional<mpz_class> TryToGetFactor(const mpz_class& number,
                                        const std::vector<uint8_t>& matrix_row,
                                        const std::vector<mpz_class>& factorized_candidates,
                                        const std::vector<size_t>& factor_base)
{
    // Check for row represents a perfect square
    for (size_t column_idx = 0; column_idx < factor_base.size(); ++column_idx) {
      if (matrix_row[column_idx] != 0)
        return std::nullopt;
    }

    bool row_has_nonzero_element = false;
    for (size_t column_idx = factor_base.size(); column_idx < 2 * factor_base.size(); ++column_idx) {
      if (matrix_row[column_idx] != 0) {
        row_has_nonzero_element = true;
        break;
      }
    }
    if (!row_has_nonzero_element)
      return std::nullopt;

    mpz_class x = 1, y = 1;
    for (size_t entry_idx = 0; entry_idx < factorized_candidates.size(); ++entry_idx) {
      if (matrix_row[factor_base.size() + entry_idx]) {
        mpz_class g_r = factorized_candidates[entry_idx] * factorized_candidates[entry_idx];
        mod(g_r, number);

        x *= g_r;
        y *= factorized_candidates[entry_idx];
      }
    }
    mpz_sqrt(x.get_mpz_t(), x.get_mpz_t());

    mpz_class possible_factor;
    mpz_gcd(possible_factor.get_mpz_t(), number.get_mpz_t(), static_cast<mpz_class>(x + y).get_mpz_t());
    if (possible_factor != 1 && possible_factor != number)
      return possible_factor;
  return std::nullopt;
}

std::optional<mpz_class> TryToGetFactorWithDixonAlgorithm(const mpz_class& number,
                                                     const std::vector<mpz_class>& sieved_entries,
                                                     const std::vector<size_t>& factor_base)
{
  auto [factored_entries, matrix] = FactorizeCandidates(number, sieved_entries, factor_base);
  BitMatrixGaussianElimination(matrix, factor_base.size());
  for (size_t i = 0; i < factored_entries.size(); i++) {
    std::optional<mpz_class> found_factor = TryToGetFactor(number, matrix[i], factored_entries, factor_base);
    if (found_factor.has_value())
      return found_factor.value();
  }
  return std::nullopt;
}

}  // namespace large_prime_numbers
