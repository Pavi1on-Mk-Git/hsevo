#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>

#include "ai/GameStateInput.h"
#include "utils/Rng.h"

/**
 * Simple evolutionary algorithm specimen
 */
class SimpleEvo
{
private:
    friend class boost::serialization::access;

    /**
     * Serialize the algorithm data into a boost archive
     * @param archive Archive to serialize the data into
     * @param version Unused
     */
    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & weights_ & mutation_strengths_;
    }

    /**
     * Algorithm weights
     */
    std::array<double, GameStateInput::INPUT_SIZE> weights_;

    /**
     * Algorithm mutation strengths
     */
    std::array<double, GameStateInput::INPUT_SIZE> mutation_strengths_;

    /**
     * Source of randomness
     */
    std::reference_wrapper<Rng> rng_;

    using ScoringFunc = std::function<std::vector<unsigned>(std::vector<SimpleEvo>)>;

    /**
     * Mutate the specimen
     */
    void mutate();

    /**
     * Initialize the population
     *
     * @param population_size The size of the population
     * @param init_mutation_strength Initial mutation strength
     * @param rng Source of randomness
     * @return Initialized population
     */
    static auto init_population(unsigned population_size, double init_mutation_strength, Rng& rng);

    /**
     * Mutate the population
     * @param population The population to mutate
     * @param mutants_size Size of the resulting mutated population
     * @param scoring_func Function to score the population with
     * @param rng Source of randomness
     */
    static auto mutate_population(
        const std::vector<SimpleEvo>& population, unsigned mutants_size, ScoringFunc scoring_func, Rng& rng
    );
public:
    /**
     * Construct a specimen
     * @param init_mutation_strength Initial mutation strength
     * @param rng Source of randomness
     */
    SimpleEvo(double init_mutation_strength, Rng& rng);

    /**
     * Construct a specimen from a stream
     * @param in Stream to load the specimen from
     * @param rng Source of randomness
     */
    SimpleEvo(std::istream& in, Rng& rng);

    /**
     * Compute the specimen score
     *
     * @param input_vec Specimen input
     * @return Computed score
     */
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;

    /**
     * Save the speciment to a stream
     *
     * @param out Stream to save the specimen to
     */
    void save(std::ostream& out) const;

    /**
     * Evolve a population of specimen using provided parameters
     *
     * @param mu Initial population size
     * @param lambda Post-mutation population size
     * @param init_mutation_strength Initial mutation strength
     * @param scoring_func Function to score the population with
     * @param iterations Number of iterations to run the algorithm for
     * @param rng Source of randomness
     */
    static std::pair<SimpleEvo, unsigned> evolve(
        unsigned mu, unsigned lambda, double init_mutation_strength, ScoringFunc scoring_func, unsigned iterations,
        Rng& rng
    );
};

#endif