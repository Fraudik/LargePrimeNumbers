#pragma once

#include <gmpxx.h>
#include <cassert>
#include <optional>

#include "../primality_status.h"
#include "../utilities.h"

namespace large_prime_numbers
{

// unproven tests -- miller not going cuz ln requres mpfr....
// with factorization can add Lucas method (and Pocklington, but not sure for now)

// сверить сканы на биты (scan1 и scan0) и побитовые штуки
// разедлить на файлы

PrimalityStatus LucasLehmerPrimalityTest(const mpz_class& mersenne_number, const mp_bitcnt_t& mersenne_power);
PrimalityStatus LucasLehmerPrimalityTestWrapper(const mpz_class& number);
PrimalityStatus LucasLehmerPrimalityTestWrapperWithCheck(const mpz_class& number);

PrimalityStatus TrialDivisionPrimalityTest(const mpz_class& number, const std::optional<mpz_class>& threshold);
PrimalityStatus TrialDivisionToSqrtPrimalityTest(const mpz_class& number);

} // namespace large_prime_numbers