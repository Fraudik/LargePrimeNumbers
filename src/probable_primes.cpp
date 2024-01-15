#include "probable_primes.h"

namespace large_prime_numbers
{

bool are_coprime(mpz_t a, mpz_t b) {
    mpz_t gcd;
    mpz_init(gcd);
    mpz_gcd(gcd, a, b);
    if (mpz_cmp_ui(gcd, 1) > 0)
    {
        mpz_clear(gcd);
        return false;
    }
    return true;
}

// Check if number is Fermat pseudoprime to chosen base
PrimalityStatus FermatProbablePrimeTest(mpz_t number, mpz_t base)
{
    mpz_t formula_result;
    mpz_t exponent;
    mpz_init(formula_result);
    mpz_init_set(exponent, number);
    mpz_sub_ui(exponent, exponent, 1);
    mpz_powm(formula_result, base, exponent, number);

    // Check if $a^(p - 1) = 1 mod p$ where $p$ is $number$ and $a$ is $base$
    if (mpz_cmp_ui(formula_result, 1) == 0)
    {
        mpz_clear(formula_result);
        mpz_clear(exponent);
        return PrimalityStatus::ProbablePrime;
    }
    else
    {
        mpz_clear(formula_result);
        mpz_clear(exponent);
        return PrimalityStatus::Composite;
    }
}

PrimalityStatus FermatProbablePrimeTestWithCheck(mpz_t number, mpz_t base)
{
    assert(are_coprime(number, base));
    return FermatProbablePrimeTest(number, base);
}

// Check if number is Euler-Jacobi pseudoprime to chosen base
PrimalityStatus EulerJacobiProbablePrimeTest(mpz_t number, mpz_t base)
{
    mpz_t left_formula_result;
    mpz_t exponent;
    mpz_init(left_formula_result);
    mpz_init_set(exponent, number);
    mpz_sub_ui(exponent, exponent, 1);
    mpz_divexact_ui(exponent, exponent, 2);
    mpz_powm(left_formula_result, base, exponent, number);

    mpz_t right_formula_result;
    int jacobi_symbol;
    mpz_init_set(right_formula_result, number);
    jacobi_symbol = mpz_jacobi(base, number);
    if (jacobi_symbol == -1)
        mpz_sub_ui(right_formula_result, right_formula_result, 1);
    else if (jacobi_symbol == 1)
        mpz_add_ui(right_formula_result, right_formula_result, 1);
    mpz_mod(right_formula_result, right_formula_result, number);

    // Check if $a^((p - 1) / 2) = JacobiSymbol(a, p) mod p$ where $p$ is $number$ and $a$ is $base$
    if (mpz_cmp(left_formula_result, right_formula_result) == 0)
    {
        mpz_clear(left_formula_result);
        mpz_clear(right_formula_result);
        return PrimalityStatus::ProbablePrime;
    }
    else
    {
        mpz_clear(left_formula_result);
        mpz_clear(right_formula_result);
        return PrimalityStatus::Composite;
    }
}

PrimalityStatus EulerJacobiProbablePrimeTestWithCheck(mpz_t number, mpz_t base)
{
    assert(are_coprime(number, base));
    return EulerJacobiProbablePrimeTest(number, base);
}

// Check if n is Miller-Rabin strong probable prime to base a
PrimalityStatus MillerRabinProbablePrimeTest(mpz_t number, mpz_t base)
{
    mpz_t number_minus_one;
    // Choose s and r satisfying equality $n = (2^r)*s + 1$ with odd s where $n$ is $number$ and $a$ is $base$
    mpz_init_set(number_minus_one, number);
    mpz_sub_ui(number_minus_one, number_minus_one, 1);
    uint64_t r = mpz_scan1(number_minus_one, 0);

    mpz_t s;
    // $s = floor((n - 1) / 2^r)$
    mpz_init_set_ui(s, 0);
    mpz_fdiv_q_2exp(s, number_minus_one, r);

    mpz_t formula_result;
    // Check if $a^s mod n = 1$ or $a^s mod n = -1 (n - 1)$ where $n$ is $number$ and $a$ is $base$
    mpz_init_set_ui(formula_result, 0);
    mpz_powm(formula_result, base, s, number);
    if ((mpz_cmp_ui(formula_result, 1) == 0) || (mpz_cmp(formula_result, number_minus_one) == 0))
    {
        mpz_clear(s);
        mpz_clear(number_minus_one);
        mpz_clear(formula_result);
        return PrimalityStatus::ProbablePrime;
    }

    // Check if $a^(2^t * s) mod n = -1 (n - 1)$ for every integer t in (0; r) where $n$ is $number$ and $a$ is $base$
    while (--r)
    {
        mpz_mul(formula_result, formula_result, formula_result);
        mpz_mod(formula_result, formula_result, number);

        if (mpz_cmp(formula_result, number_minus_one) == 0)
        {
            mpz_clear(s);
            mpz_clear(number_minus_one);
            mpz_clear(formula_result);
            return PrimalityStatus::ProbablePrime;
        }
    }

    mpz_clear(s);
    mpz_clear(number_minus_one);
    mpz_clear(formula_result);
    return PrimalityStatus::Composite;
}

// Let D, P and Q be such that D = P^2 - 4Q != 0 and P > 0
// Also $gcd(n, Q) = 1$
void LucasPreconditionsCheck(mpz_t number, int64_t p, int64_t q)
{
    assert(p > 0);
    mpz_t gmp_q;
    mpz_init_set_si(gmp_q, q);
    assert(are_coprime(number, gmp_q));
    assert((p * p - 4 * q) != 0);
}

PrimalityStatus LucasProbablePrimeTest(mpz_t number, int64_t p, int64_t q)
{
    int64_t d = p * p - 4 * q;
    mpz_t gmp_d;
    mpz_init_set_si(gmp_d, d);

    // Also some congurences are hold provided $gcd(number, D) = 1$
    // Consider this part of the test because D is not chosen based on the number tested
    if (!are_coprime(number, gmp_d))
    {
        mpz_clear(gmp_d);
        return PrimalityStatus::Composite;
    }

    mpz_t delta_n;
    // $delta_n = n - JacobiSymbol(D/n)$
    mpz_init_set(delta_n, number);
    int ret = mpz_jacobi(gmp_d, number);
    if (ret == -1)
        mpz_add_ui(delta_n, delta_n, 1);
    else if (ret == 1)
        mpz_sub_ui(delta_n, delta_n, 1);

    // Calculating Lucas sequences
    mpz_t u_h, v_l, v_h, q_l, q_h, temp;
    mpz_init_set_si(u_h, 1);
    mpz_init_set_si(v_l, 2);
    mpz_init_set_si(v_h, p);
    mpz_init_set_si(q_l, 1);
    mpz_init_set_si(q_h, 1);
    mpz_set_si(temp, 0);

    int s = mpz_scan1(delta_n, 0);
    int j;
    for (j = mpz_sizeinbase(delta_n, 2) - 1; j >= s + 1; --j)
    {
        // q_l = q_l*q_h (mod n)
        mpz_mul(q_l, q_l, q_h);
        mpz_mod(q_l, q_l, number);
        if (mpz_tstbit(delta_n, j) == 1)
        {
            // q_h = q_l * q
            mpz_mul_si(q_h, q_l, q);

            // u_h = u_h * v_h (mod n)
            mpz_mul(u_h, u_h, v_h);
            mpz_mod(u_h, u_h, number);

            // v_l = v_h * v_l - p * q_l (mod n)
            mpz_mul(v_l, v_h, v_l);
            mpz_mul_si(temp, q_l, p);
            mpz_sub(v_l, v_l, temp);
            mpz_mod(v_l, v_l, number);

            // v_h = v_h * v_h - 2 * q_h (mod n)
            mpz_mul(v_h, v_h, v_h);
            mpz_mul_si(temp, q_h, 2);
            mpz_sub(v_h, v_h, temp);
            mpz_mod(v_h, v_h, number);
        }
        else
        {
            // q_h = q_l
            mpz_set(q_h, q_l);

            // u_h = u_h * v_l - q_l (mod n)
            mpz_mul(u_h, u_h, v_l);
            mpz_sub(u_h, u_h, q_l);
            mpz_mod(u_h, u_h, number);

            // v_h = v_h * v_l - p * q_l (mod n)
            mpz_mul(v_h, v_h, v_l);
            mpz_mul_si(temp, q_l, p);
            mpz_sub(v_h, v_h, temp);
            mpz_mod(v_h, v_h, number);

            // v_l = v_l * v_l - 2 * q_l (mod n)
            mpz_mul(v_l, v_l, v_l);
            mpz_mul_si(temp, q_l, 2);
            mpz_sub(v_l, v_l, temp);
            mpz_mod(v_l, v_l, number);
        }
    }
    // q_l = q_l * q_h
    mpz_mul(q_l, q_l, q_h);

    // q_h = q_l * q
    mpz_mul_si(q_h, q_l, q);

    // u_h = u_h * v_l - q_l
    mpz_mul(u_h, u_h, v_l);
    mpz_sub(u_h, u_h, q_l);

    // v_l = v_h * v_l - p * q_l
    mpz_mul(v_l, v_h, v_l);
    mpz_mul_si(temp, q_l, p);
    mpz_sub(v_l, v_l, temp);

    // q_l = q_l * q_h
    mpz_mul(q_l, q_l, q_h);

    for (j = 1; j <= s; j++)
    {
        // u_h = u_h * v_l (mod n)
        mpz_mul(u_h, u_h, v_l);
        mpz_mod(u_h, u_h, number);

        // v_l = v_l * v_l - 2 * q_l (mod n)
        mpz_mul(v_l, v_l, v_l);
        mpz_mul_si(temp, q_l, 2);
        mpz_sub(v_l, v_l, temp);
        mpz_mod(v_l, v_l, number);

        // q_l = q_l * q_l (mod n)
        mpz_mul(q_l, q_l, q_l);
        mpz_mod(q_l, q_l, number);
    }

    mpz_mod(u_h, u_h, number);

    mpz_clear(gmp_d);
    mpz_clear(delta_n);
    mpz_clear(v_l);
    mpz_clear(v_h);
    mpz_clear(q_l);
    mpz_clear(q_h);
    mpz_clear(temp);

    if (mpz_cmp_ui(u_h, 0) == 0)
    {
        mpz_clear(u_h);
        return PrimalityStatus::ProbablePrime;
    }
    else
    {
        mpz_clear(u_h);
        return PrimalityStatus::Composite;
    }
}

PrimalityStatus LucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q)
{
    LucasPreconditionsCheck(number, p, q);
    return LucasProbablePrimeTest(number, p, q);
}

PrimalityStatus StrongLucasProbablePrimeTest(mpz_t number, int64_t p, int64_t q)
{
    int64_t d = p * p - 4 * q;
    mpz_t gmp_d;
    mpz_init_set_si(gmp_d, d);

    // Also some congurences are hold provided $gcd(number, D) = 1$
    // Consider this part of the test because D is not chosen based on the number tested
    if (!are_coprime(number, gmp_d))
    {
        mpz_clear(gmp_d);
        return PrimalityStatus::Composite;
    }

    mpz_t delta_n;
    // delta_n = n - JacobiSymbol(D/n)
    mpz_init_set(delta_n, number);
    int ret = mpz_jacobi(gmp_d, number);
    if (ret == -1)
        mpz_add_ui(delta_n, delta_n, 1);
    else if (ret == 1)
        mpz_sub_ui(delta_n, delta_n, 1);

    mpz_t t;
    // Decomposition: $delta_n = t * 2^s$
    // Further will be checked if $U_t = 0 (mod n)$ or exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
    uint64_t r = mpz_scan1(delta_n, 0);
    mpz_init(t);
    mpz_fdiv_q_2exp(t, delta_n, r);

    mpz_t u_h, v_l, v_h, q_l, q_h, temp;
    mpz_init_set_si(u_h, 1);
    mpz_init_set_si(v_l, 2);
    mpz_init_set_si(v_h, p);
    mpz_init_set_si(q_l, 1);
    mpz_init_set_si(q_h, 1);
    mpz_set_si(temp, 0);

    size_t j;
    for (j = mpz_sizeinbase(t, 2) - 1; j >= 1; --j)
    {
        // q_l = q_l * q_h (mod n)
        mpz_mul(q_l, q_l, q_h);
        mpz_mod(q_l, q_l, number);
        if (mpz_tstbit(t, j) == 1)
        {
            // q_h = q_l * q
            mpz_mul_si(q_h, q_l, q);

            // u_h = u_h * v_h (mod n)
            mpz_mul(u_h, u_h, v_h);
            mpz_mod(u_h, u_h, number);

            // v_l = v_h * v_l - p * q_l (mod n)
            mpz_mul(v_l, v_h, v_l);
            mpz_mul_si(temp, q_l, p);
            mpz_sub(v_l, v_l, temp);
            mpz_mod(v_l, v_l, number);

            // v_h = v_h * v_h - 2 * q_h (mod n)
            mpz_mul(v_h, v_h, v_h);
            mpz_mul_si(temp, q_h, 2);
            mpz_sub(v_h, v_h, temp);
            mpz_mod(v_h, v_h, number);
        }
        else
        {
            // q_h = q_l
            mpz_set(q_h, q_l);

            // u_h = u_h * v_l - q_l (mod n)
            mpz_mul(u_h, u_h, v_l);
            mpz_sub(u_h, u_h, q_l);
            mpz_mod(u_h, u_h, number);

            // v_h = v_h * v_l - p * q_l (mod n)
            mpz_mul(v_h, v_h, v_l);
            mpz_mul_si(temp, q_l, p);
            mpz_sub(v_h, v_h, temp);
            mpz_mod(v_h, v_h, number);

            // v_l = v_l * v_l - 2 * q_l (mod n)
            mpz_mul(v_l, v_l, v_l);
            mpz_mul_si(temp, q_l, 2);
            mpz_sub(v_l, v_l, temp);
            mpz_mod(v_l, v_l, number);
        }
    }

    // q_l = q_l * q_h
    mpz_mul(q_l, q_l, q_h);

    // q_h = q_l * q
    mpz_mul_si(q_h, q_l, q);

    // u_h = u_h * v_l - q_l
    mpz_mul(u_h, u_h, v_l);
    mpz_sub(u_h, u_h, q_l);

    // v_l = v_h * v_l - p * q_l
    mpz_mul(v_l, v_h, v_l);
    mpz_mul_si(temp, q_l, p);
    mpz_sub(v_l, v_l, temp);

    // q_l = q_l * q_h
    mpz_mul(q_l, q_l, q_h);

    mpz_mod(u_h, u_h, number);
    mpz_mod(v_l, v_l, number);

    // u_h = U_t and v_l = V_t of Lucas sequences
    // Checking if U_t = 0 (mod n)$ or $V_(t * 2^0) = 0 (mod n)$
    if ((mpz_cmp_ui(u_h, 0) == 0) || (mpz_cmp_ui(v_l, 0) == 0))
    {
        mpz_clear(gmp_d);
        mpz_clear(t);
        mpz_clear(delta_n);
        mpz_clear(u_h);
        mpz_clear(v_l);
        mpz_clear(v_h);
        mpz_clear(q_l);
        mpz_clear(q_h);
        mpz_clear(temp);
        return PrimalityStatus::ProbablePrime;
    }

    // Checking if exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
    for (j = 1; j < r; ++j)
    {
        // v_l = v_l * v_l - 2 * q_l (mod n)
        mpz_mul(v_l, v_l, v_l);
        mpz_mul_si(temp, q_l, 2);
        mpz_sub(v_l, v_l, temp);
        mpz_mod(v_l, v_l, number);

        // q_l = q_l * q_l (mod n)
        mpz_mul(q_l, q_l, q_l);
        mpz_mod(q_l, q_l, number);

        if (mpz_cmp_ui(v_l, 0) == 0)
        {
            mpz_clear(gmp_d);
            mpz_clear(t);
            mpz_clear(delta_n);
            mpz_clear(u_h);
            mpz_clear(v_l);
            mpz_clear(v_h);
            mpz_clear(q_l);
            mpz_clear(q_h);
            mpz_clear(temp);
            return PrimalityStatus::ProbablePrime;
        }
    }

    mpz_clear(gmp_d);
    mpz_clear(t);
    mpz_clear(delta_n);
    mpz_clear(u_h);
    mpz_clear(v_l);
    mpz_clear(v_h);
    mpz_clear(q_l);
    mpz_clear(q_h);
    mpz_clear(temp);
    return PrimalityStatus::Composite;
}

PrimalityStatus StrongLucasProbablePrimeTestWithCheck(mpz_t number, int64_t p, int64_t q)
{
    LucasPreconditionsCheck(number, p, q);
    return StrongLucasProbablePrimeTest(number, p, q);
}

// If number is a perfect square, no required D will exist
LucasTestParameters CalculateSelfridgeParametersForLucasTest(mpz_t number, int64_t max_d = 100'000)
{
    assert(!mpz_perfect_square_p(number));

    int64_t d = 5, p = 1, q;
    mpz_t gmp_d;
    mpz_init_set_ui(gmp_d, d);

    int jacobi_symbol;
    while (true)
    {
        jacobi_symbol = mpz_jacobi(gmp_d, number);

        // If jacobi_symbol is 0, then D is a factor of number
        if (jacobi_symbol == 0)
        {
            if (mpz_cmpabs(gmp_d, number) == 0)
            {
                mpz_clear(gmp_d);
                return LucasTestParameters{p, q, PrimalityStatus::Prime};
            }
            else
            {
                mpz_clear(gmp_d);
                return LucasTestParameters{p, q, PrimalityStatus::Composite};
            }
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
        {
            mpz_clear(gmp_d);
            assert(d >= max_d);
        }

        mpz_set_si(gmp_d, d);
    }
    mpz_clear(gmp_d);

    q = (1 - d) / 4;

    return LucasTestParameters{p, q, PrimalityStatus::ProbablePrime};
}

PrimalityStatus BPSWPrimalityTest(mpz_t number)
{
    mpz_t two;
    mpz_init_set_ui(two, 2);
    auto mr_test_result = MillerRabinProbablePrimeTest(number, two);
    mpz_clear(two);

    if (mr_test_result != PrimalityStatus::ProbablePrime)
        return mr_test_result;

    auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(number);
    if (selfridge_parameters.pre_test_status != PrimalityStatus::ProbablePrime)
        return selfridge_parameters.pre_test_status;

    return StrongLucasProbablePrimeTestWithCheck(number, selfridge_parameters.p, selfridge_parameters.q);
}

}
