#pragma once

#include <gmpxx.h>

#include "probable_primes.h"

namespace large_prime_numbers
{

PrimalityStatus BasicPrimalityChecks(mpz_t number)
{
    if (mpz_cmp_ui(number, 2) < 0)
        return PrimalityStatus::Composite;
    if (mpz_cmp_ui(number, 2) == 0)
        return PrimalityStatus::Prime;
    if (mpz_divisible_ui_p(number, 2))
        return PrimalityStatus::Composite;
    if (mpz_perfect_square_p(number))
        return PrimalityStatus::Composite;
    return PrimalityStatus::ProbablePrime;
}

template <class PrimalityTest, class... TestSpecificArgs>
bool PrimalityTestWrapper(mpz_t number, PrimalityTest primality_test, TestSpecificArgs &&... args)
{
    PrimalityStatus test_result = BasicPrimalityChecks(number);
    if (test_result == PrimalityStatus::ProbablePrime)
        test_result = primality_test(number, std::forward<TestSpecificArgs>(args)...);
    if (test_result == PrimalityStatus::Composite)
        return false;
    return true;
}

// В дальнейшем будут добавляться какие-то прослойки, вроде подбора дополнительных параметров для запуска тестов
//  (или запуск сразу нескольких тестов с разными параметрами)
}
