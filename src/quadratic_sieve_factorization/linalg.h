#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

// Using the smallest available and efficient type (due to performance issues of vector<bool>)
using BitMatrix = std::vector<std::vector<uint8_t>>;

void BitMatrixGaussianElimination(BitMatrix& matrix, size_t amount_of_columns);

} // namespace large_prime_numbers
