#pragma once

#include <gmpxx.h>

namespace large_prime_numbers
{

class GMPRandomGenerator
{
public:
    GMPRandomGenerator(mpz_class low_threshold, mpz_class high_threshold) :
        low_threshold_(std::move(low_threshold)), high_threshold_(std::move(high_threshold))
    {}

    void setSeed(const mpz_class& seed)
    {
        generator_engine_.seed(seed);
    }

    // generate value in range [low_threshold; high_threshold]
    mpz_class generateValue()
    {
        // [0; high_threshold_ - low_threshold_ + 1) + low_threshold_
        return generator_engine_.get_z_range(high_threshold_ - low_threshold_ + 1) + low_threshold_;
    }

private:
    mpz_class low_threshold_;
    mpz_class high_threshold_;
    gmp_randclass generator_engine_ = gmp_randclass(gmp_randinit_default);
};

} // namespace large_prime_numbers
