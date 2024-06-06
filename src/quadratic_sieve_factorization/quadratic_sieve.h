#pragma once

#include <optional>
#include <gmpxx.h>

#include "sieving.h"

namespace large_prime_numbers
{

std::optional<mpz_class> TryToGetFactorWithQuadraticSieve(const mpz_class& number,
                                                  const QuadraticSieveConstantParameters& parameters);

} //  namespace large_prime_numbers
