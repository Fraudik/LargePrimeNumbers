#include <cassert>

#include "../utilities.h"
#include "lucas_pseudoprimes.h"
#include "probable_primality_tests.h"

namespace large_prime_numbers
{

namespace
{

// Check if number is Fermat pseudoprime to chosen base
// Check if $a^(p - 1) = 1 mod p$ where $p$ is $number$ and $a$ is $base$
PrimalityStatus FermatProbablePrimeTest(const mpz_class& number, const mpz_class& base)
{
    mpz_class formula_result;
    mpz_powm(formula_result.get_mpz_t(), base.get_mpz_t(), static_cast<mpz_class>(number - 1).get_mpz_t(),
             number.get_mpz_t());
    if (formula_result == 1)
        return PrimalityStatus::ProbablePrime;
    return PrimalityStatus::Composite;
}

// Check if number is Euler-Jacobi pseudoprime to chosen base
// if $a^((p - 1) / 2) = JacobiSymbol(a, p) mod p$ where $p$ is $number$ and $a$ is $base$
PrimalityStatus EulerJacobiProbablePrimeTest(const mpz_class& number, const mpz_class& base)
{
    mpz_class left_formula_result;
    mpz_class exponent = number - 1;
    mpz_divexact_ui(exponent.get_mpz_t(), exponent.get_mpz_t(), 2);
    mpz_powm(left_formula_result.get_mpz_t(), base.get_mpz_t(), exponent.get_mpz_t(), number.get_mpz_t());

    int jacobi_symbol = mpz_jacobi(base.get_mpz_t(), number.get_mpz_t());
    mpz_class right_formula_result = 1;
    if (jacobi_symbol == -1)
        right_formula_result = number - 1;

    if (left_formula_result == right_formula_result)
        return PrimalityStatus::ProbablePrime;
    return PrimalityStatus::Composite;
}

}

PrimalityStatus FermatProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base)
{
    assert(are_coprime(number, base));
    return FermatProbablePrimeTest(number, base);
}

PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(const mpz_class& number, const mpz_class& base)
{
    assert(are_coprime(number, base));
    assert(number % 2 != 0);
    return EulerJacobiProbablePrimeTest(number, base);
}

// Check if n is Miller-Rabin strong probable prime to base a
// Check if $a^s mod n = 1$ or $a^(2^t * s) mod n = -1$ for every integer t in [0; r) where $n$ is $number$ and $a$ is $base$
PrimalityStatus MillerRabinProbablePrimeTest(const mpz_class& number, const mpz_class& base)
{
    mpz_class number_minus_one{number - 1};
    auto decomposition = decompose_in_powers_of_two(number_minus_one);
    uint64_t r = decomposition.power_of_two;
    mpz_class s = std::move(decomposition.odd_multiplier);

    mpz_class formula_result{0};
    // Check if $a^s mod n = 1$ or $a^s mod n = -1 (n - 1)$ where $n$ is $number$ and $a$ is $base$
    mpz_powm(formula_result.get_mpz_t(), base.get_mpz_t(), s.get_mpz_t(), number.get_mpz_t());
    if (formula_result == 1 || formula_result == number_minus_one)
        return PrimalityStatus::ProbablePrime;
    // Check if $a^(2^t * s) = -1 \pmod n$ for every integer t in (0; r) where $n$ is $number$ and $a$ is $base$
    while (--r)
    {
        formula_result *= formula_result;
        mod(formula_result, number);
        if (formula_result == number_minus_one)
            return PrimalityStatus::ProbablePrime;
    }
    return PrimalityStatus::Composite;
}

PrimalityStatus BPSWPrimalityTest(const mpz_class& number)
{
    auto mr_test_result = MillerRabinProbablePrimeTest(number, mpz_class{2});

    if (mr_test_result != PrimalityStatus::ProbablePrime)
        return mr_test_result;

    return StrongLucasProbablePrimeTestWithSelfridgeParameters(number);
}

PrimalityStatus EnhancedBPSWPrimalityTest(const mpz_class& number)
{
    auto mr_test_result = MillerRabinProbablePrimeTest(number, mpz_class{2});

    if (mr_test_result != PrimalityStatus::ProbablePrime)
        return mr_test_result;

    return EnhancedStrongLucasProbablePrimeTestWithSelfridgeParameters(number);
}

} // namespace large_prime_numbers
