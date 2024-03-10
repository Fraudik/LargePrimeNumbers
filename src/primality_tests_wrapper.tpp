#pragma once

#include <gmpxx.h>

#include "probable_primality_tests.h"

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

template <class PrimalityTest>
bool PrimalityTestWithRandomBaseWrapper(const mpz_class& number, PrimalityTest primality_test, const std::optional<mpz_class>& seed)
{
    PrimalityStatus test_result = BasicPrimalityChecks(number);
    if (test_result == PrimalityStatus::ProbablePrime)
    {
        GMPRandomGenerator random_generator(2, number - 1);
        if (seed != std::nullopt)
        {
            random_generator.setSeed(*seed);
        }
        mpz_class random_base = random_generator.generateValue();
        if (!are_coprime(number, random_base))
        {
            return false;
        }
        test_result = primality_test(number, random_base);
    }

    if (test_result == PrimalityStatus::Composite)
        return false;
    return true;
}

// В дальнейшем будут добавляться какие-то прослойки, вроде подбора дополнительных параметров для запуска тестов
//  (или запуск сразу нескольких тестов с разными параметрами)

} // namespace large_prime_numbers
