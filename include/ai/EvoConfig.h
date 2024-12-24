#ifndef EVO_CONFIG_H
#define EVO_CONFIG_H

#include <string>

struct EvoConfig
{
    /**
     * Initial population size
     */
    unsigned mu;

    /**
     * Mutant population size
     */
    unsigned lambda;

    /**
     * Initial mutation strength
     */
    double init_mutation_strength;

    /**
     * Human-readable name of the configuration
     * @return Name of the configuration
     */
    std::string name() const;
};

#endif