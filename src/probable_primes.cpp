#include <gmpxx.h>

#include "primality_tests_wrapper.h"

PrimalityStatus FermatProbablePrimeTest(mpz_t a, mpz_t p) {
  mpz_t intermediate_result;
  mpz_init_set_ui(intermediate_result, 0);
  mpz_gcd(intermediate_result, a, p);

  // Checking if $gcd(a,p) = 1$
  if (mpz_cmp_ui(intermediate_result, 1) > 0) {
    mpz_clear(intermediate_result);
    return Composite;
  }

  mpz_t temp;
  mpz_init_set(temp, p);
  mpz_sub_ui(temp, temp, 1);
  mpz_powm(intermediate_result, a, temp, p);

  // Check if  $a^(p-1) = 1 mod p$
  if (mpz_cmp_ui(intermediate_result, 1) == 0) {
    mpz_clear(intermediate_result);
    mpz_clear(temp);
    return ProbablePrime;
  } else {
    mpz_clear(intermediate_result);
    mpz_clear(temp);
    return Composite;
  }
}

PrimalityStatus EulerJacobiProbablePrimeTest(mpz_t a, mpz_t p) {
  mpz_t intermediate_result;
  mpz_init_set_ui(intermediate_result, 0);
  mpz_gcd(intermediate_result, a, p);

  // Checking if $gcd(a,p) = 1$
  if (mpz_cmp_ui(intermediate_result, 1) > 0) {
    mpz_clear(intermediate_result);
    return Composite;
  }

  mpz_t temp;
  mpz_init_set(temp, p);
  mpz_sub_ui(temp, temp, 1);
  mpz_divexact_ui(temp, temp, 2);
  mpz_powm(intermediate_result, a, temp, p);

  int jacobi_symbol = 0;
  jacobi_symbol = mpz_jacobi(a, p);
  // Reusing temp for right part of equation
  mpz_set(temp, p);
  if (jacobi_symbol == -1)
    mpz_sub_ui(temp, temp, 1);
  else if (jacobi_symbol == 1)
    mpz_add_ui(temp, temp, 1);
  mpz_mod(temp, temp, p);

  // Check if $a^(p-1)/2 = JacobiSymbol(a, p) mod p$
  if (mpz_cmp(intermediate_result, temp) == 0) {
    mpz_clear(intermediate_result);
    mpz_clear(temp);
    return ProbablePrime;
  } else {
    mpz_clear(intermediate_result);
    mpz_clear(temp);
    return Composite;
  }
}

PrimalityStatus MillerRabinProbablePrimeTest(mpz_t a, mpz_t p) {
  mpz_t temp;
  // Choose s and r satisfying equality $p = (2^r)*s + 1$ with odd s
  mpz_init_set(temp, p);
  mpz_sub_ui(temp, temp, 1);
  uint64_t r = mpz_scan1(temp, 0);

  mpz_t s;
  // s = floor( (p - 1) / 2 ^ r )
  mpz_init_set_ui(s, 0);
  mpz_fdiv_q_2exp(s, temp, r);

  mpz_t intermediate_result;
  // Check if $a^s mod p= 1$ or $a^s mod p = -1 (p - 1)$
  mpz_init_set_ui(intermediate_result, 0);
  mpz_powm(intermediate_result, a, s, p);
  if ((mpz_cmp_ui(intermediate_result, 1) == 0) || (mpz_cmp(intermediate_result, temp) == 0)) {
    mpz_clear(s);
    mpz_clear(temp);
    mpz_clear(intermediate_result);
    return ProbablePrime;
  }

  // Check if $a^(2^t * s) mod p = -1 (p - 1)$ for every integer t in (0; r)
  while (--r) {
    mpz_mul(intermediate_result, intermediate_result, intermediate_result);
    mpz_mod(intermediate_result, intermediate_result, p);

    if (mpz_cmp(intermediate_result, temp) == 0) {
      mpz_clear(s);
      mpz_clear(temp);
      mpz_clear(intermediate_result);
      return ProbablePrime;
    }
  }

  mpz_clear(s);
  mpz_clear(temp);
  mpz_clear(intermediate_result);
  return Composite;
}

PrimalityStatus LucasProbablePrimeTest(mpz_t n, int64_t p, int64_t q) {
  int64_t d = p * p - 4 * q;

  // Can not produce required Lucas sequence
  if (d == 0) {
    return Error;
  }
  // Converting D to gmp format
  mpz_t gmp_d;
  mpz_init_set_si(gmp_d, d);

  mpz_t temp;
  // Checking if $gcd(n, 2QD) <> 1$ and $gcd(n, 2QD) <> n$
  mpz_init(temp);
  mpz_mul_si(temp, gmp_d, q);
  mpz_mul_ui(temp, temp, 2);
  mpz_gcd(temp, temp, n);
  if ((mpz_cmp(temp, n) != 0) && (mpz_cmp_ui(temp, 1) != 0)) {
    mpz_clear(gmp_d);
    mpz_clear(temp);
    return Composite;
  }

  mpz_t delta_n;
  // delta_n = n - JacobiSymbol(D/n)
  mpz_init_set(delta_n, n);
  int ret = mpz_jacobi(gmp_d, n);
  if (ret == -1) {
    mpz_add_ui(delta_n, delta_n, 1);
  } else if (ret == 1) {
    mpz_sub_ui(delta_n, delta_n, 1);
  }

  // Calculating Lucas sequences
  mpz_t u_h, v_l, v_h, q_l, q_h;
  mpz_init_set_si(u_h, 1);
  mpz_init_set_si(v_l, 2);
  mpz_init_set_si(v_h, p);
  mpz_init_set_si(q_l, 1);
  mpz_init_set_si(q_h, 1);
  mpz_set_si(temp, 0);

  int s = mpz_scan1(delta_n, 0);
  int j;
  for (j = mpz_sizeinbase(delta_n, 2) - 1; j >= s + 1; --j) {
    // q_l = q_l*q_h (mod n) 
    mpz_mul(q_l, q_l, q_h);
    mpz_mod(q_l, q_l, n);
    if (mpz_tstbit(delta_n, j) == 1) {
      // q_h = q_l * q
      mpz_mul_si(q_h, q_l, q);

      // u_h = u_h * v_h (mod n)
      mpz_mul(u_h, u_h, v_h);
      mpz_mod(u_h, u_h, n);

      // v_l = v_h * v_l - p * q_l (mod n)
      mpz_mul(v_l, v_h, v_l);
      mpz_mul_si(temp, q_l, p);
      mpz_sub(v_l, v_l, temp);
      mpz_mod(v_l, v_l, n);

      // v_h = v_h * v_h - 2 * q_h (mod n)
      mpz_mul(v_h, v_h, v_h);
      mpz_mul_si(temp, q_h, 2);
      mpz_sub(v_h, v_h, temp);
      mpz_mod(v_h, v_h, n);
    } else {
      // q_h = q_l 
      mpz_set(q_h, q_l);

      // u_h = u_h * v_l - q_l (mod n)
      mpz_mul(u_h, u_h, v_l);
      mpz_sub(u_h, u_h, q_l);
      mpz_mod(u_h, u_h, n);

      // v_h = v_h * v_l - p * q_l (mod n)
      mpz_mul(v_h, v_h, v_l);
      mpz_mul_si(temp, q_l, p);
      mpz_sub(v_h, v_h, temp);
      mpz_mod(v_h, v_h, n);

      // v_l = v_l * v_l - 2 * q_l (mod n)
      mpz_mul(v_l, v_l, v_l);
      mpz_mul_si(temp, q_l, 2);
      mpz_sub(v_l, v_l, temp);
      mpz_mod(v_l, v_l, n);
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

  for (j = 1; j <= s; j++) {
    // u_h = u_h * v_l (mod n)
    mpz_mul(u_h, u_h, v_l);
    mpz_mod(u_h, u_h, n);

    // v_l = v_l * v_l - 2 * q_l (mod n)
    mpz_mul(v_l, v_l, v_l);
    mpz_mul_si(temp, q_l, 2);
    mpz_sub(v_l, v_l, temp);
    mpz_mod(v_l, v_l, n);

    // q_l = q_l * q_l (mod n)
    mpz_mul(q_l, q_l, q_l);
    mpz_mod(q_l, q_l, n);
  }

  mpz_mod(u_h, u_h, n);

  mpz_clear(gmp_d);
  mpz_clear(delta_n);
  mpz_clear(v_l);
  mpz_clear(v_h);
  mpz_clear(q_l);
  mpz_clear(q_h);
  mpz_clear(temp);

  if (mpz_cmp_ui(u_h, 0) == 0) {
    mpz_clear(u_h);
    return ProbablePrime;
  } else {
    mpz_clear(u_h);
    return Composite;
  }
}

PrimalityStatus StrongLucasProbablePrimeTest(mpz_t n, long int p, long int q) {
  int64_t d = p * p - 4 * q;

  // Can not produce required Lucas sequence
  if (d == 0) {
    return Error;
  }
  // Converting D to gmp format
  mpz_t gmp_d;
  mpz_init_set_si(gmp_d, d);

  mpz_t temp;
  // Checking if $gcd(n, 2QD) <> 1$ and $gcd(n, 2QD) <> n$
  mpz_init(temp);
  mpz_mul_si(temp, gmp_d, q);
  mpz_mul_ui(temp, temp, 2);
  mpz_gcd(temp, temp, n);
  if ((mpz_cmp(temp, n) != 0) && (mpz_cmp_ui(temp, 1) != 0)) {
    mpz_clear(gmp_d);
    mpz_clear(temp);
    return Composite;
  }

  mpz_t delta_n;
  // delta_n = n - JacobiSymbol(D/n)
  mpz_init_set(delta_n, n);
  int ret = mpz_jacobi(gmp_d, n);
  if (ret == -1) {
    mpz_add_ui(delta_n, delta_n, 1);
  } else if (ret == 1) {
    mpz_sub_ui(delta_n, delta_n, 1);
  }

  mpz_t t;
  // Decomposition: delta_n = t * 2^s
  // Further will be checked if $U_t = 0 (mod n)$ or exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
  uint64_t r = mpz_scan1(delta_n, 0);
  mpz_init(t);
  mpz_fdiv_q_2exp(t, delta_n, r);

  mpz_t u_h, v_l, v_h, q_l, q_h;
  mpz_init_set_si(u_h, 1);
  mpz_init_set_si(v_l, 2);
  mpz_init_set_si(v_h, p);
  mpz_init_set_si(q_l, 1);
  mpz_init_set_si(q_h, 1);
  mpz_set_si(temp, 0);

  int j;
  for (j = mpz_sizeinbase(t, 2) - 1; j >= 1; --j) {
    // q_l = q_l * q_h (mod n)
    mpz_mul(q_l, q_l, q_h);
    mpz_mod(q_l, q_l, n);
    if (mpz_tstbit(t, j) == 1) {
      // q_h = q_l * q
      mpz_mul_si(q_h, q_l, q);

      // u_h = u_h * v_h (mod n)
      mpz_mul(u_h, u_h, v_h);
      mpz_mod(u_h, u_h, n);

      // v_l = v_h * v_l - p * q_l (mod n)
      mpz_mul(v_l, v_h, v_l);
      mpz_mul_si(temp, q_l, p);
      mpz_sub(v_l, v_l, temp);
      mpz_mod(v_l, v_l, n);

      // v_h = v_h * v_h - 2 * q_h (mod n)
      mpz_mul(v_h, v_h, v_h);
      mpz_mul_si(temp, q_h, 2);
      mpz_sub(v_h, v_h, temp);
      mpz_mod(v_h, v_h, n);
    } else {
      // q_h = q_l 
      mpz_set(q_h, q_l);

      // u_h = u_h * v_l - q_l (mod n)
      mpz_mul(u_h, u_h, v_l);
      mpz_sub(u_h, u_h, q_l);
      mpz_mod(u_h, u_h, n);

      // v_h = v_h * v_l - p * q_l (mod n)
      mpz_mul(v_h, v_h, v_l);
      mpz_mul_si(temp, q_l, p);
      mpz_sub(v_h, v_h, temp);
      mpz_mod(v_h, v_h, n);

      // v_l = v_l * v_l - 2 * q_l (mod n)
      mpz_mul(v_l, v_l, v_l);
      mpz_mul_si(temp, q_l, 2);
      mpz_sub(v_l, v_l, temp);
      mpz_mod(v_l, v_l, n);
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

  mpz_mod(u_h, u_h, n);
  mpz_mod(v_l, v_l, n);

  // u_h = U_t and v_l = V_t of Lucas sequences
  // Checking if U_t = 0 (mod n)$ or $V_(t * 2^0) = 0 (mod n)$
  if ((mpz_cmp_ui(u_h, 0) == 0) || (mpz_cmp_ui(v_l, 0) == 0)) {
    mpz_clear(gmp_d);
    mpz_clear(t);
    mpz_clear(delta_n);
    mpz_clear(u_h);
    mpz_clear(v_l);
    mpz_clear(v_h);
    mpz_clear(q_l);
    mpz_clear(q_h);
    mpz_clear(temp);
    return ProbablePrime;
  }

  // Checking if exists r in [0; s) that $V_(t * 2^r) = 0 (mod n)$
  for (j = 1; j < r; j++) {
    // v_l = v_l * v_l - 2 * q_l (mod n)
    mpz_mul(v_l, v_l, v_l);
    mpz_mul_si(temp, q_l, 2);
    mpz_sub(v_l, v_l, temp);
    mpz_mod(v_l, v_l, n);

    // q_l = q_l * q_l (mod n)
    mpz_mul(q_l, q_l, q_l);
    mpz_mod(q_l, q_l, n);

    if (mpz_cmp_ui(v_l, 0) == 0) {
      mpz_clear(gmp_d);
      mpz_clear(t);
      mpz_clear(delta_n);
      mpz_clear(u_h);
      mpz_clear(v_l);
      mpz_clear(v_h);
      mpz_clear(q_l);
      mpz_clear(q_h);
      mpz_clear(temp);
      return ProbablePrime;
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
  return Composite;
}

struct LucasTestParameters {
  int64_t p;
  int64_t q;
  // When calculating parameters for Lucas test,
  //  it is possible to immediately detect that the number is composite or prime (or to throw Error)
  PrimalityStatus pre_test_status;
};

LucasTestParameters CalculateSelfridgeParametersForLucasTest(mpz_t n, int64_t max_d = 100'000) {
  int64_t d = 5, p = 1, q;
  mpz_t gmp_d;

  mpz_init_set_ui(gmp_d, d);

  if (mpz_perfect_square_p(n)) {
    mpz_clear(gmp_d);
    return LucasTestParameters{p, q, Composite};
  }

  int jacobi_symbol;
  while (true) {
    jacobi_symbol = mpz_jacobi(gmp_d, n);

    // If jacobi_symbol is 0, then D is a factor of N
    if (jacobi_symbol == 0) {
      if (mpz_cmpabs(gmp_d, n) == 0) {
        mpz_clear(gmp_d);
        return LucasTestParameters{p, q, Prime};
      } else {
        mpz_clear(gmp_d);
        return LucasTestParameters{p, q, Composite};
      }
    }

    // Found required D
    if (jacobi_symbol == -1)
      break;

    if (d < 0) {
      d *= -1;
      d += 2;
    } else {
      d += 2;
      d *= -1;
    }

    // If not found such d in range to max_d
    if (d >= max_d) {
      mpz_clear(gmp_d);
      return LucasTestParameters{p, q, Error};
    }

    mpz_set_si(gmp_d, d);
  }
  mpz_clear(gmp_d);

  q = (1 - d) / 4;

  return LucasTestParameters{p, q, ProbablePrime};
}

PrimalityStatus BPSWPrimalityTest(mpz_t n) {
  mpz_t two;
  mpz_init_set_ui(two, 2);
  auto mr_test_result = MillerRabinProbablePrimeTest(n, two);
  mpz_clear(two);

  if (mr_test_result != ProbablePrime)
    return mr_test_result;

  auto selfridge_parameters = CalculateSelfridgeParametersForLucasTest(n);
  if (selfridge_parameters.pre_test_status != ProbablePrime)
    return selfridge_parameters.pre_test_status;

  return StrongLucasProbablePrimeTest(n, selfridge_parameters.p, selfridge_parameters.q);
}
