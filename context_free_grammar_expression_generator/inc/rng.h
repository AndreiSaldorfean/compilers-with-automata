#pragma once
#include <cstdint>
#include <random>


class Rng{
    typedef std::mt19937 rng_type;
    std::random_device rd;
    rng_type::result_type seedval;
    int64_t min;
    int64_t max;
public:
    Rng(uint64_t seed,int64_t min, int64_t max);
    int64_t generate();
};
