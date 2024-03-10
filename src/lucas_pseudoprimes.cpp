#include "lucas_pseudoprimes.h"
#include <cmath>
#include <iostream>

namespace large_prime_numbers
{

// Let D, P and Q be such that D = P^2 - 4Q != 0 and P > 0
// Also $gcd(n, Q) = 1$ and $gcd(n, D) = 1$
bool LucasPreconditionsCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(p > 0);

    mpz_class gmp_q(q);
    assert(are_coprime(number, gmp_q));

    mpz_class gmp_d = p * p - 4 * q;
    assert(gmp_d != 0);
    assert(are_coprime(number, gmp_d));

    // bool type for putting function into assert
    return true;
}

PrimalityStatus LucasVCheck(const mpz_class& V_n, const mpz_class& number, int64_t p, int64_t q)
{
    // checking if V_n = 2 * Q^{ (1 - JacobiSymbol(D/n)) / 2 }
    mpz_class gmp_d = p * p - 4 * q;
    int jacobi_symbol = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (jacobi_symbol == 1 && V_n == 2)
        return PrimalityStatus::ProbablePrime;
    mpz_class right_equation_side = 2 * q;
    mod(right_equation_side, number);
    if (jacobi_symbol == -1 && V_n == right_equation_side)
        return PrimalityStatus::ProbablePrime;
    return PrimalityStatus::Composite;
}

LucasSequenceMembers LucasSequenceCalculation(const mpz_class& number, int64_t p, int64_t q)
{
    int64_t d = p * p - 4 * q;
    mpz_class gmp_d{d};

    // $delta_n = n - JacobiSymbol(D/n)$
    mpz_class delta_n{number};
    int ret = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (ret == -1)
        delta_n += 1;
    else if (ret == 1)
        delta_n -= 1;

    // Calculating Lucas sequences
    mpz_class u_h{1}, v_l{2}, v_h{p}, q_l{1}, q_h{1};

    int s = mpz_scan1(delta_n.get_mpz_t(), 0);

    size_t j;
    for (j = mpz_sizeinbase(delta_n.get_mpz_t(), 2) - 1; j >= s + 1; --j)
    {
        q_l *= q_h;
        mod(q_l, number);
        if (mpz_tstbit(delta_n.get_mpz_t(), j) == 1)
        {
            q_h = q_l * q;

            u_h *= v_h;
            mod(u_h, number);

            v_l = v_h * v_l - q_l * p;
            mod(v_l, number);

            v_h = v_h * v_h - q_h * 2;
            mod(v_h, number);
        }
        else
        {
            q_h = q_l;

            u_h = u_h * v_l - q_l;
            mod(u_h, number);

            v_h = v_h * v_l - q_l * p;
            mod(v_h, number);

            v_l = v_l * v_l - q_l * 2;
            mod(v_l, number);
        }
    }

    q_l *= q_h;
    q_h = q_l * q;

    u_h = u_h * v_l - q_l;
    v_l = v_h * v_l - q_l * p;

    q_l *= q_h;

    for (j = 1; j <= s; j++)
    {
        u_h *= v_l;
        mod(u_h, number);

        v_l = v_l * v_l - q_l * 2;
        mod(v_l, number);

        q_l *= q_l;
        mod(q_l, number);
    }

    return {u_h, v_l};
}

PrimalityStatus LucasProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    auto calculated_members = LucasSequenceCalculation(number, p, q);
    if (calculated_members.U_n == 0)
        return PrimalityStatus::ProbablePrime;
    return PrimalityStatus::Composite;
}

PrimalityStatus LucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return LucasProbablePrimeTest(number, p, q);
}

PrimalityStatus LucasVProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    auto calculated_members = LucasSequenceCalculation(number, p, q);
    return LucasVCheck(calculated_members.V_n, number, p, q);
}

PrimalityStatus LucasVProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return LucasVProbablePrimeTest(number, p, q);
}

LucasSequenceMembers AcceleratedLucasSequenceCalculation(const mpz_class& number, int64_t p, int64_t q)
{
    int64_t d = p * p - 4 * q;
    mpz_class gmp_d{d};

    // $delta_n = n - JacobiSymbol(D/n)$
    mpz_class delta_n{number};
    int ret = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (ret == -1)
        delta_n += 1;
    else if (ret == 1)
        delta_n -= 1;

    // Calculating Lucas sequences
    mpz_class v_l{2}, v_h{p}, q_l{1}, q_h{1};
    int s = mpz_scan1(delta_n.get_mpz_t(), 0);
    int64_t j;
    for (j = mpz_sizeinbase(delta_n.get_mpz_t(), 2) - 1; j >= 0; --j)
    {
        q_l *= q_h;
        mod(q_l, number);
        if (mpz_tstbit(delta_n.get_mpz_t(), j) == 1)
        {
            q_h = q_l * q;

            v_l = v_h * v_l - q_l * p;
            mod(v_l, number);

            v_h = v_h * v_h - q_h * 2;
            mod(v_h, number);
        }
        else
        {
            q_h = q_l;

            v_h = v_h * v_l - q_l * p;
            mod(v_h, number);

            v_l = v_l * v_l - q_l * 2;
            mod(v_l, number);
        }
    }

    mpz_class u_k;
    u_k = (2 * v_h - p * v_l);
    mod(u_k, number);
    u_k /= (p * p - 4 * q);
    return {u_k, v_l};
}

PrimalityStatus AcceleratedLucasProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    auto calculated_members = AcceleratedLucasSequenceCalculation(number, p, q);
    if (calculated_members.U_n == 0)
        return PrimalityStatus::ProbablePrime;
    return PrimalityStatus::Composite;
}

PrimalityStatus AcceleratedLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return AcceleratedLucasProbablePrimeTest(number, p, q);
}

PrimalityStatus AcceleratedLucasVProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    auto calculated_members = AcceleratedLucasSequenceCalculation(number, p, q);
    return LucasVCheck(calculated_members.V_n, number, p, q);
}

PrimalityStatus AcceleratedLucasVProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return AcceleratedLucasVProbablePrimeTest(number, p, q);
}

PrimalityStatus StrongLucasProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    int64_t d = p * p - 4 * q;
    mpz_class gmp_d{d};

    // delta_n = n - JacobiSymbol(D/n)
    mpz_class delta_n{number};
    int ret = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (ret == -1)
        delta_n += 1;
    else if (ret == 1)
        delta_n -= 1;

    auto decomposition = decompose_in_powers_of_two(delta_n);
    uint64_t r = decomposition.power_of_two;
    mpz_class t = decomposition.odd_multiplier;
    // Further will be checked if $U_t = 0 (mod n)$ or exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$

    mpz_class u_h{1}, v_l{2}, v_h{p}, q_l{1}, q_h{1};
    size_t j;
    for (j = mpz_sizeinbase(t.get_mpz_t(), 2) - 1; j >= 1; --j)
    {
        q_l *= q_h;
        mod(q_l, number);
        if (mpz_tstbit(t.get_mpz_t(), j) == 1)
        {
            q_h = q_l * q;

            u_h *= v_h;
            mod(u_h, number);

            v_l = v_h * v_l - q_l * p;
            mod(v_l, number);

            v_h = v_h * v_h - q_h * 2;
            mod(v_h, number);
        }
        else
        {
            q_h = q_l;

            u_h = u_h * v_l - q_l;
            mod(u_h, number);

            v_h = v_h * v_l - q_l * p;
            mod(v_h, number);

            v_l = v_l * v_l - q_l * 2;
            mod(v_l, number);
        }
    }

    q_l *= q_h;
    q_h = q_l * q;

    u_h = u_h * v_l - q_l;
    mod(u_h, number);
    v_l = v_h * v_l - q_l * p;
    mod(v_l, number);

    q_l *= q_h;

    // u_h = U_t and v_l = V_t of Lucas sequences
    // Checking if U_t = 0 (mod n)$ or $V_(t * 2^0) = 0 (mod n)$
    if (u_h == 0 || v_l == 0)
        return PrimalityStatus::ProbablePrime;

    // Checking if exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
    for (j = 1; j < r; ++j)
    {
        v_l = v_l * v_l - q_l * 2;
        mod(v_l, number);

        q_l *= q_l;
        mod(q_l, number);

        if (v_l == 0)
            return PrimalityStatus::ProbablePrime;
    }
    return PrimalityStatus::Composite;
}

PrimalityStatus StrongLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return StrongLucasProbablePrimeTest(number, p, q);
}

PrimalityStatus EnhancedStrongLucasProbablePrimeTest(const mpz_class& number, int64_t p, int64_t q)
{
    // this particular test gives an error with 3 as corner case
    if (number == 3)
        return PrimalityStatus::Prime;

    int64_t d = p * p - 4 * q;
    mpz_class gmp_d{d};

    // delta_n = n - JacobiSymbol(D/n)
    mpz_class delta_n{number};
    int ret = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (ret == -1)
        delta_n += 1;
    else if (ret == 1)
        delta_n -= 1;

    auto decomposition = decompose_in_powers_of_two(delta_n);
    uint64_t r = decomposition.power_of_two;
    mpz_class t = decomposition.odd_multiplier;
    // Further will be checked if $U_t = 0 (mod n)$ or exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$

    mpz_class u_h{1}, v_l{2}, v_h{p}, q_l{1}, q_h{1};
    size_t j;
    for (j = mpz_sizeinbase(t.get_mpz_t(), 2) - 1; j >= 1; --j)
    {
        q_l *= q_h;
        mod(q_l, number);
        if (mpz_tstbit(t.get_mpz_t(), j) == 1)
        {
            q_h = q_l * q;

            u_h *= v_h;
            mod(u_h, number);

            v_l = v_h * v_l - q_l * p;
            mod(v_l, number);

            v_h = v_h * v_h - q_h * 2;
            mod(v_h, number);
        }
        else
        {
            q_h = q_l;

            u_h = u_h * v_l - q_l;
            mod(u_h, number);

            v_h = v_h * v_l - q_l * p;
            mod(v_h, number);

            v_l = v_l * v_l - q_l * 2;
            mod(v_l, number);
        }
    }

    q_l *= q_h;
    q_h = q_l * q;

    u_h = u_h * v_l - q_l;
    mod(u_h, number);
    v_l = v_h * v_l - q_l * p;
    mod(v_l, number);

    q_l *= q_h;

    PrimalityStatus primality_state = PrimalityStatus::Composite;

    // u_h = U_t and v_l = V_t of Lucas sequences
    // Checking if U_t = 0 (mod n)$ or $V_(t * 2^0) = 0 (mod n)$
    if (u_h == 0 || v_l == 0)
        primality_state = PrimalityStatus::ProbablePrime;

    // Checking if exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
    for (j = 1; j < r; ++j)
    {
        v_l = v_l * v_l - q_l * 2;
        mod(v_l, number);

        q_l *= q_l;
        mod(q_l, number);

        if (v_l == 0)
            primality_state = PrimalityStatus::ProbablePrime;
    }

    // check if $V_{\delta(n)} \equiv 2Q^{ ((1 - JacobiSymbol(D / n)) / 2} \pmod{n}$
    v_l = v_l * v_l - q_l * 2;
    mod(v_l, number);
    PrimalityStatus v_check_result = LucasVCheck(v_l, number, p, q);
    if (v_check_result == PrimalityStatus::Composite)
        return v_check_result;

    // performing Euler test with Q as base
    mod(q_l, number);
    int jacobi_symbol_of_d = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());
    if (jacobi_symbol_of_d == 1)
    {
        q_l *= q;
        mod(q_l, number);
    }
    mpz_class gmp_q = q;
    int jacobi_symbol_of_q = mpz_jacobi(gmp_q.get_mpz_t(), number.get_mpz_t());
    mpz_class right_equation_side = q * jacobi_symbol_of_q;
    mod(right_equation_side, number);
    if (q_l != right_equation_side)
        return PrimalityStatus::Composite;

    if (v_l == 0)
        primality_state = PrimalityStatus::ProbablePrime;
    return primality_state;
}

PrimalityStatus EnhancedStrongLucasProbablePrimeTestWithCheck(const mpz_class& number, int64_t p, int64_t q)
{
    assert(LucasPreconditionsCheck(number, p, q));
    return EnhancedStrongLucasProbablePrimeTest(number, p, q);
}

// If number is a perfect square, no required D will exist
SelfridgeDetail::LucasTestParameters CalculateSelfridgeParametersForLucasTest(const mpz_class& number, int64_t max_d)
{
    assert(!mpz_perfect_square_p(number.get_mpz_t()));

    int64_t d = 5, p = 1, q;
    mpz_class gmp_d{d};

    int jacobi_symbol;
    while (true)
    {
        jacobi_symbol = mpz_jacobi(gmp_d.get_mpz_t(), number.get_mpz_t());

        // If jacobi_symbol is 0, then D is a factor of number
        if (jacobi_symbol == 0)
        {
            if (abs(gmp_d) == abs(number))
                return SelfridgeDetail::LucasTestParameters{p, q, PrimalityStatus::Prime};
            return SelfridgeDetail::LucasTestParameters{p, q, PrimalityStatus::Composite};
        }

        // Found required D
        if (jacobi_symbol == -1)
            break;

        if (d < 0)
        {
            d *= -1;
            d += 2;
        }
        else
        {
            d += 2;
            d *= -1;
        }

        // If not found such d in range to max_d
        if (d >= max_d)
            assert(d >= max_d);

        gmp_d = d;
    }

    q = (1 - d) / 4;
    // Method A*
    if (q == -1)
    {
        p = 5;
        q = 5;
    }
    return SelfridgeDetail::LucasTestParameters{p, q, PrimalityStatus::ProbablePrime};
}

PrimalityStatus LucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d)
{
    auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(number, max_d);
    if (selfridge_parameters.pre_test_status != PrimalityStatus::ProbablePrime)
        return selfridge_parameters.pre_test_status;
    return LucasProbablePrimeTestWithCheck(number, selfridge_parameters.p, selfridge_parameters.q);
}

PrimalityStatus AcceleratedLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d)
{
    auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(number, max_d);
    if (selfridge_parameters.pre_test_status != PrimalityStatus::ProbablePrime)
        return selfridge_parameters.pre_test_status;
    return AcceleratedLucasProbablePrimeTestWithCheck(number, selfridge_parameters.p, selfridge_parameters.q);
}

PrimalityStatus StrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d)
{
    auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(number, max_d);
    if (selfridge_parameters.pre_test_status != PrimalityStatus::ProbablePrime)
        return selfridge_parameters.pre_test_status;
    return StrongLucasProbablePrimeTestWithCheck(number, selfridge_parameters.p, selfridge_parameters.q);
}

PrimalityStatus EnhancedStrongLucasProbablePrimeTestWithSelfridgeParameters(const mpz_class& number, int64_t max_d)
{
    auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(number, max_d);
    if (selfridge_parameters.pre_test_status != PrimalityStatus::ProbablePrime)
        return selfridge_parameters.pre_test_status;
    return EnhancedStrongLucasProbablePrimeTestWithCheck(number, selfridge_parameters.p, selfridge_parameters.q);
}

} // namespace large_prime_numbers
