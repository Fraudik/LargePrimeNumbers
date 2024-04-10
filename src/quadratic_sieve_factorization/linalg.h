#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

using BitMatrix = std::vector<std::vector<bool>>;

void BitMatrixGaussianElimination(BitMatrix& matrix, size_t amount_of_columns);

} // namespace large_prime_numbers
