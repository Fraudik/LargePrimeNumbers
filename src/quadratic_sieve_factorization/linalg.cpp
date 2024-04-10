#include <cassert>

#include "linalg.h"

namespace large_prime_numbers
{

namespace
{

void row_xor(std::vector<bool>& lhs_row, const std::vector<bool>& rhs_row) {
  assert(lhs_row.size() == rhs_row.size());
  for (size_t j = 0; j != lhs_row.size(); ++j) {
    lhs_row[j] = lhs_row[j] ^ rhs_row[j];
  }
}

}

void BitMatrixGaussianElimination(BitMatrix& matrix, size_t amount_of_columns) {
  for (size_t i = 0; i < amount_of_columns; ++i) {
    // Search for pivot row
    size_t pivot_row_idx = i;
    while (pivot_row_idx < matrix.size() && !matrix[pivot_row_idx][i]) {
      ++pivot_row_idx;
    }
    if (pivot_row_idx == matrix.size())
      continue;
    // Push pivot row to top
    if (pivot_row_idx != i)
      std::swap(matrix[i], matrix[pivot_row_idx]);
    // Eliminate rows under with pivot row
    for (size_t j = i + 1; j < matrix.size(); ++j) {
      if (matrix[j][i]) {
        row_xor(matrix[j], matrix[i]);
      }
    }
  }
}

} // namespace large_prime_numbers
