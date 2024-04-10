#include <iostream>

#include "except.h"
#include "primality_tests_wrapper.h"
#include "probable_prime_tests/probable_primality_tests.h"
#include "common/utilities.h"
#include "quadratic_sieve_factorization/multiple_polynomial_quadratic_sieve.h"


namespace
{

// For further development I expect this to move to another file in /programs dir
void ExampleNumberPrimalityCheck(const mpz_class& number)
{
    auto rez = large_prime_numbers::PrimalityTestWrapper(number, large_prime_numbers::EnhancedBPSWPrimalityTest);
    if (rez)
        std::cout << "This number is prime" << std::endl;
    else
        std::cout << "This number is composite" << std::endl;
}

}

int main(int argc, char** argv)
{
//    if (argc < 2)
//    {
//        std::cout << "Enter a number to check for primality" << std::endl;
//        exit(1);
//    }
//    try
//    {
//        // here will be call of finite state machine with input checking and starting corresponding test
//        mpz_class gmp_number_class(argv[1]);
//        ExampleNumberPrimalityCheck(gmp_number_class);
//    }
//    catch (...)
//    {
//        except::react();
//    }
    return 0;
}
