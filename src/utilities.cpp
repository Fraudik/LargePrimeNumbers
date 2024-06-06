#include "utilities.h"

namespace large_prime_numbers
{

bool are_coprime(const mpz_class& a, const mpz_class& b)
{
    mpz_class gcd;
    mpz_gcd(gcd.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return gcd <= 1;
}

TwoPowersDecomposition decompose_in_powers_of_two(const mpz_class& a)
{
    TwoPowersDecomposition decomposition;
    decomposition.power_of_two = mpz_scan1(a.get_mpz_t(), 0);
    // $odd_multiplier = floor(a / 2^power_of_two)$
    mpz_fdiv_q_2exp((decomposition.odd_multiplier).get_mpz_t(), a.get_mpz_t(), decomposition.power_of_two);
    return decomposition;
}

} // namespace large_prime_numbers
