#pragma once

#include <optional>
#include <gmpxx.h>

#include "probable_primes.h"

namespace large_prime_numbers
{

template <class PrimalityTest, class... TestSpecificArgs>
bool PrimalityTestWrapper(mpz_t n, PrimalityTest primality_test, TestSpecificArgs&&... args)
{
    if (mpz_cmp_ui(n, 2) < 0)
        return false;
    if (mpz_cmp_ui(n, 2) == 0)
        return true;
    if (mpz_divisible_ui_p(n, 2))
        return false;

    auto test_result = primality_test(n, std::forward<TestSpecificArgs>(args)...);
    if (test_result == PrimalityStatus::Composite)
        return false;
    return true;
}

// В дальнейшем будут добавляться какие-то прослойки, вроде подбора дополнительных параметров для запуска тестов
//  (или запуск сразу нескольких тестов с разными параметрами)
}
