#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include "ai/EvoSpecimen.hpp"

/**
 * Simple evolutionary algorithm
 */
class SimpleEvo
{
private:
    /**
     * Source of randomness
     */
    Rng& rng_;

    /**
     * Population size
     */
    unsigned mu_;

    /**
     * Mutant population size
     */
    unsigned lambda_;

    /**
     * Current population
     */
    std::vector<EvoSpecimen> population_;

    /**
     * Scores of the population
     */
    std::vector<unsigned> scores_;

    /**
     * Mutate the population
     */
    void mutate();
public:
    /**
     * Construct an instance of evolutionary algorithm
     *
     * @param mu Initial population size
     * @param lambda Post-mutation population size
     * @param init_mutation_strength Initial mutation strength
     * @param rng Source of randomness
     */
    SimpleEvo(unsigned mu, unsigned lambda, double init_mutation_strength, Rng& rng);

    /**
     * Return specimen for the current population
     *
     * @return Vector of specimen
     */
    const std::vector<EvoSpecimen>& get_population() const;

    /**
     * Assign scores to current population
     *
     * @param scores Scores to assign
     * @return The best specimen along with its score
     */
    std::pair<EvoSpecimen, unsigned> assign_scores(const std::vector<unsigned>& scores);

    /**
     * Advance the algorithm by a single epoch
     */
    void epoch();
};

#endif
