#include <cassert>

#include "deterministic_primality_tests.h"
#include "../utilities.h"

namespace large_prime_numbers
{

namespace
{

PrimalityStatus LucasLehmerPrimalityTest(const mpz_class& mersenne_number, size_t mersenne_power)
{
    mpz_class sequence_member = 4;
    for (size_t i = 0; i < mersenne_power - 2; ++i)
    {
        sequence_member = ((sequence_member * sequence_member) - 2);
        mod(sequence_member, mersenne_number);
    }
    if (sequence_member == 0)
        return PrimalityStatus::Prime;
    return PrimalityStatus::Composite;
}

PrimalityStatus LucasLehmerPrimalityTestWrapper(const mpz_class& number)
{
    size_t mersenne_power = mpz_scan0(number.get_mpz_t(), 0);
    return LucasLehmerPrimalityTest(number, mersenne_power);
}

}

PrimalityStatus LucasLehmerPrimalityTestWrapperWithCheck(const mpz_class& number)
{
    assert((number & (number + 1)) == 0);
    return LucasLehmerPrimalityTestWrapper(number);
}

PrimalityStatus TrialDivisionPrimalityTest(const mpz_class& number, const mpz_class& threshold)
{
    if (number % 2 == 0)
        return PrimalityStatus::Composite;
    for (mpz_class i = 3; i <= threshold; i += 2)
        if (number % i == 0)
            return PrimalityStatus::Composite;
    return PrimalityStatus::ProbablePrime;
}

PrimalityStatus TrialDivisionToSqrtPrimalityTest(const mpz_class& number)
{
    mpz_class threshold;
    // mpz_sqrt gives truncated sqrt
    mpz_sqrt(threshold.get_mpz_t(), number.get_mpz_t());

    auto test_result = TrialDivisionPrimalityTest(number, threshold);
    // if iterating over $\sqrt(number) + 1$ and no factors were found during the trial division, such a number is prime
    if (test_result == PrimalityStatus::ProbablePrime)
        return PrimalityStatus::Prime;
    return PrimalityStatus::Composite;
}

} // namespace large_prime_numbers
