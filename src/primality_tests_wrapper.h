#pragma once

#include <gmpxx.h>
#include <optional>

#include "utilities.h"
#include "random_generator.h"
#include "probable_prime_tests/probable_primality_tests.h"

namespace large_prime_numbers
{

inline PrimalityStatus BasicPrimalityChecks(const mpz_class& number)
{
    if (number == 1)
      return PrimalityStatus::NeitherPrimeOrComposite;
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
    assert(number > 0);
    PrimalityStatus test_result = BasicPrimalityChecks(number);
    if (test_result == PrimalityStatus::ProbablePrime)
        test_result = primality_test(number, std::forward<TestSpecificArgs>(args)...);
    // Return true only for prime numbers
    return (test_result != PrimalityStatus::Composite && test_result != PrimalityStatus::NeitherPrimeOrComposite);
}

template <class PrimalityTest>
bool PrimalityTestWithRandomBaseWrapper(const mpz_class& number, PrimalityTest primality_test,
                                        const std::optional<mpz_class>& seed)
{
    assert(number > 0);
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

    // Return true only for prime numbers
    return (test_result != PrimalityStatus::Composite && test_result != PrimalityStatus::NeitherPrimeOrComposite);
}

} // namespace large_prime_numbers
