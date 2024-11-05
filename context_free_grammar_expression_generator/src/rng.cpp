#include "rng.h"
#include <cstdint>
#include <ctime>
#include <cstdlib>

Rng::Rng(uint64_t seed,int64_t min, int64_t max){
    this->min = min;
    this->max = max;
    seedval = seed;

    std::srand(std::time(0));
}

int64_t Rng::generate(){
    std::mt19937 gen(seedval);
    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}