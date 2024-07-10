#ifndef RNG_H
#define RNG_H

#include <memory>
#include <random>

class Rng
{
private:
    std::ranlux24 random_engine_;
    static std::unique_ptr<Rng> instance_;
    Rng();
public:
    static std::unique_ptr<Rng>& instance();
    void seed(int seed_nr);
    int uniform_int(int min, int max);
    double uniform_real(double min = 0., double max = 1.);
    std::ranlux24& generator();
    friend std::unique_ptr<Rng> std::make_unique<Rng>();
};

#endif