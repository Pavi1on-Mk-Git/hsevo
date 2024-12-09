#ifndef RNG_H
#define RNG_H

#include <memory>
#include <random>

class Rng
{
private:
    std::ranlux24 random_engine_;
public:
    Rng(unsigned seed_nr);
    int uniform_int(int min, int max);
    double uniform_real(double min = 0., double max = 1.);
    double normal(double mean = 0., double stddev = 1.);
    std::ranlux24& generator();
};

#endif