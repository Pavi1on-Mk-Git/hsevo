#ifndef RNG_H
#define RNG_H

#include <memory>
#include <random>

/**
 * Source of randomness
 */
class Rng
{
private:
    /**
     * Underlying random engine
     */
    std::ranlux24 random_engine_;
public:
    /**
     * Construct a source of randomness
     * @param seed_nr Seed used in the generator
     */
    Rng(unsigned seed_nr);

    /**
     * Return a random integer from uniform distribution
     * @param min Minimum number which could be generated
     * @param max Maximum number which could be generated plus one
     * @return Random integer
     */
    int uniform_int(int min, int max);

    /**
     * Return a random real number from uniform distribution
     * @param min Minimum number which could be generated
     * @param max Maximum number which could be generated
     * @return Random real number
     */
    double uniform_real(double min = 0., double max = 1.);

    /**
     * Return a random real number from normal distribution
     * @param mean Mean of the distribution
     * @param stddev Standard deviation of the distribution
     * @return Random real number from range
     */
    double normal(double mean = 0., double stddev = 1.);

    /**
     * Return the underlying random engine
     * @return Random engine
     */
    std::ranlux24& generator();
};

#endif