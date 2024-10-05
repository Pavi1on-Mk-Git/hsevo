#include "utils/Rng.h"

Rng::Rng() {}

Rng* Rng::instance_ = nullptr;

Rng* Rng::instance()
{
    return instance_ ? instance_ : (instance_ = new Rng());
}

void Rng::seed(int seed_nr)
{
    random_engine_.seed(seed_nr);
}

std::ranlux24& Rng::generator()
{
    return random_engine_;
}

int Rng::uniform_int(int min, int max)
{
    return std::uniform_int_distribution(min, max)(random_engine_);
}

double Rng::uniform_real(double min, double max)
{
    return std::uniform_real_distribution(min, max)(random_engine_);
}

double Rng::normal(double mean, double stddev)
{
    return std::normal_distribution(mean, stddev)(random_engine_);
}