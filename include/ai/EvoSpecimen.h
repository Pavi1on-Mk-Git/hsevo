#ifndef EVO_SPECIMEN_HPP
#define EVO_SPECIMEN_HPP

#include "ai/GameStateInput.h"
#include "utils/Rng.h"

/**
 * Evolutionary algorithm specimen
 */
class EvoSpecimen
{
private:
    /**
     * Algorithm mutation strengths
     */
    std::array<double, GameStateInput::INPUT_SIZE> mutation_strengths_;

    /**
     * Source of randomness
     */
    std::reference_wrapper<Rng> rng_;
public:
    /**
     * Algorithm weights
     */
    std::array<double, GameStateInput::INPUT_SIZE> weights;

    /**
     * Construct a specimen
     * @param init_mutation_strength Initial mutation strength
     * @param rng Source of randomness
     */
    EvoSpecimen(double init_mutation_strength, Rng& rng);

    /**
     * Mutate the specimen
     */
    void mutate();
};

#endif
