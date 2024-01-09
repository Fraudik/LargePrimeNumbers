#include <iostream>

#include "primality_tests_wrapper.h"
#include "probable_primes.cpp"

// For further development I expect this to move to another file in /programs dir
void ExampleNumberPrimalityCheck(mpz_t number)
{
  auto rez = PrimalityTestWrapper(number, BPSWPrimalityTest);
  if (rez)
  {
    std::cout << "This number is prime" << std::endl;
  }
  else
  {
    std::cout << "This number is composite" << std::endl;
  }
}

int main(int argc, char ** argv)
{
  if (argc < 2) {
      std::cout << "Enter a number to check for primality" << std::endl;
      exit(1);
  }
  mpz_class gmp_number_class(argv[1]);
  // here will be call of finite state machine with input checking and starting corresponding test
  try
  {
    ExampleNumberPrimalityCheck(gmp_number_class.get_mpz_t());
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what();
  }
  return 0;
}
