#include <map>
#include <cassert>

#include "quadratic_congruences_solving.h"
#include "../utilities.h"
#include "../random_generator.h"

namespace large_prime_numbers
{
namespace
{

mpz_class CalculateV(const mpz_class& final_idx, const mpz_class& prime, const mpz_class& h, const mpz_class& n)
{
  // Using map to cache calculated values
  std::map<mpz_class, mpz_class> v;
  v[1] = h;
  v[2] = h * h - 2 * n;
  mod(v[2], prime);

  // Passing without explicitly specifying v, because of implicitly capture in a lambda with no capture-default specified
  std::function<mpz_class(mpz_class)> calculate_v_by_idx = [&](const mpz_class& idx) {
    if (v.find(idx) != v.end()) {
      return v[idx];
    }

    if (idx % 2 == 0) {
      // $ v_idx = (v_{idx / 2})^2 - 2 \cdot n^{idx / 2} $
      mpz_class minuend;
      mpz_powm_ui(minuend.get_mpz_t(),
                  static_cast<mpz_class>(calculate_v_by_idx(idx / 2)).get_mpz_t(), 2,
                  prime.get_mpz_t());
      mpz_class subtrahend;
      mpz_powm(subtrahend.get_mpz_t(),
               n.get_mpz_t(), static_cast<mpz_class>(idx / 2).get_mpz_t(),
               prime.get_mpz_t());
      v[idx] = minuend - 2 * subtrahend;
    } else {
      // $ v_idx = v_{idx / 2} \cdot v_{idx / 2 + 1} - h \cdot n^{idx / 2} $
      mpz_class subtrahend;
      mpz_powm(subtrahend.get_mpz_t(),
               n.get_mpz_t(), static_cast<mpz_class>(idx / 2).get_mpz_t(),
               prime.get_mpz_t());
      v[idx] = calculate_v_by_idx(idx / 2) * calculate_v_by_idx(idx / 2 + 1) - h * subtrahend;
    }
    return v[idx];
  };

  return calculate_v_by_idx(final_idx);
}

mpz_class CalculateOneQuadraticCongruence(mpz_class quadratic_residue, const mpz_class& prime)
{
  auto random_generator = GMPRandomGenerator(0, prime - 1);
  random_generator.setSeed(42);

  // Analog for null value - to avoid (while true) cycle
  mpz_class h = prime;
  while (h == prime) {
    auto possible_h = random_generator.generateValue();
    mpz_class legendre_numerator = static_cast<mpz_class>(possible_h) * possible_h - 4 * static_cast<mpz_class>(quadratic_residue);
    mod(legendre_numerator, prime);
    if (mpz_legendre(legendre_numerator.get_mpz_t(), prime.get_mpz_t()) == -1) {
      h = possible_h;
    }
  }

  mod(quadratic_residue, prime);
  mpz_class v = CalculateV((prime + 1) / 2, prime, h, quadratic_residue);
  mpz_class congruence_solution = v * ((prime + 1) / 2);
  mod(congruence_solution, prime);
  return congruence_solution;
}

}

std::vector<mpz_class> CalculateQuadraticCongruences(const mpz_class& quadratic_residue, const mpz_class& odd_prime)
{
  assert(odd_prime % 2 != 0);
  mpz_class quadratic_congruence = CalculateOneQuadraticCongruence(quadratic_residue, odd_prime);
  return {quadratic_congruence, odd_prime - quadratic_congruence};
}

}  // namespace large_prime_numbers
