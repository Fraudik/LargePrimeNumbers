#include <iostream>

#include "except.h"
#include "primality_tests_wrapper.tpp"
#include "probable_primality_tests.h"

namespace
{

// For further development I expect this to move to another file in /programs dir
void ExampleNumberPrimalityCheck(const mpz_class& number)
{
    large_prime_numbers::BPSWPrimalityTest;
    auto rez = large_prime_numbers::PrimalityTestWrapper(number, large_prime_numbers::BPSWPrimalityTest);
    if (rez)
        std::cout << "This number is prime" << std::endl;
    else
        std::cout << "This number is composite" << std::endl;
}

}

int main(int argc, char** argv)
{
    mpz_class a{62};
    auto x = mpz_scan0(a.get_mpz_t(), 0);
    std::cout << x;
    return 0;
    if (argc < 2)
    {
        std::cout << "Enter a number to check for primality" << std::endl;
        exit(1);
    }
    try
    {
        // here will be call of finite state machine with input checking and starting corresponding test
        mpz_class gmp_number_class(argv[1]);
        ExampleNumberPrimalityCheck(gmp_number_class);
    }
    catch (...)
    {
        except::react();
    }
    return 0;
}
