#pragma once

#include <gmpxx.h>

enum PrimalityStatus {
  Prime,
  Composite,
  ProbablePrime,
  Error
};

template<class PrimalityTest, class ... TestSpecificArgs>
bool PrimalityTestWrapper(mpz_t n, PrimalityTest primality_test, TestSpecificArgs...args) {
  if (mpz_cmp_ui(n, 2) < 0)
    return false;

  if (mpz_divisible_ui_p(n, 2)) {
    if (mpz_cmp_ui(n, 2) == 0)
      return true;
    else
      return false;
  }

  auto test_result = primality_test(n, args...);
  if (test_result == Error)
    throw std::runtime_error("Wrong args for primality test");
  if (test_result == Composite)
    return false;
  return true;
}

// В дальнейшем будут добавляться какие-то прослойки, вроде подбора дополнительных параметров для запуска тестов
//  (или запуск сразу нескольких тестов с разными параметрами)