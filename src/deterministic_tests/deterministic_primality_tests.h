#pragma once

#include <gmpxx.h>
#include <cassert>
#include <optional>

#include "../primality_status.h"
#include "../utilities.h"

namespace large_prime_numbers
{

PrimalityStatus LucasLehmerPrimalityTestWrapperWithCheck(const mpz_class& number);

PrimalityStatus TrialDivisionPrimalityTest(const mpz_class& number, const std::optional<mpz_class>& threshold);
PrimalityStatus TrialDivisionToSqrtPrimalityTest(const mpz_class& number);

} // namespace large_prime_numbers