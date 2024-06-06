#include <gmpxx.h>
#include <gtest/gtest.h>

#include "primality_tests_wrapper.h"
#include "utilities.h"

namespace large_prime_numbers
{

template <class PrimalityTest, class... TestSpecificArgs>
void CheckOnListOfLowPrimes(const std::string& test_name, PrimalityTest primality_test, TestSpecificArgs&&... args)
{
    FileReader file("primes_2_to_99991.txt");
    EXPECT_TRUE(file.IsOpen()) << "Can not open file with primes";

    std::vector<int64_t> low_primes;
    file >> low_primes;
    for (const mpz_class& prime : low_primes)
    {
        bool is_test_marked_prime = PrimalityTestWrapper(prime,
                                                         primality_test, std::forward<TestSpecificArgs>(args)...);
        EXPECT_TRUE(is_test_marked_prime) << test_name + " marked " << prime << " as not prime";
    }
}

}
