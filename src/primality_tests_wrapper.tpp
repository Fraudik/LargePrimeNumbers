#pragma once

#include <gmpxx.h>

#include "probable_primes.h"

namespace large_prime_numbers
{

inline PrimalityStatus BasicPrimalityChecks(const mpz_class& number)
{
    if (number < 2)
        return PrimalityStatus::Composite;
    if (number == 2)
        return PrimalityStatus::Prime;
    if (number % 2 == 0)
        return PrimalityStatus::Composite;
    if (mpz_perfect_square_p(number.get_mpz_t()))
        return PrimalityStatus::Composite;
    return PrimalityStatus::ProbablePrime;
}

template <class PrimalityTest, class... TestSpecificArgs>
bool PrimalityTestWrapper(const mpz_class& number, PrimalityTest primality_test, TestSpecificArgs &&... args)
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
