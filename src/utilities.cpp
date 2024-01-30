#include "utilities.h"

namespace large_prime_numbers
{

bool are_coprime(const mpz_class& a, const mpz_class& b) {
    mpz_class gcd;
    mpz_gcd(gcd.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    if (gcd > 1)
    {
        return false;
    }
    return true;
}

}