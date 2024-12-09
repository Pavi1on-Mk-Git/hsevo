#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>
#include <iostream>

#include "ai/GameStateInput.h"
#include "utils/Rng.h"

class SimpleEvo
{
private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & weights_ & mutation_strengths_;
    }

    std::array<double, GameStateInput::INPUT_SIZE> weights_;
    std::array<double, GameStateInput::INPUT_SIZE> mutation_strengths_;

    std::reference_wrapper<Rng> rng_;

    using ScoringFunc = std::function<std::vector<unsigned>(std::vector<SimpleEvo>)>;

    void mutate();
    static auto init_population(unsigned population_size, double init_mutation_strength, Rng& rng);

    static auto mutate_population(
        const std::vector<SimpleEvo>& population, unsigned mutants_size, ScoringFunc scoring_func, Rng& rng
    );
public:
    SimpleEvo(double init_mutation_strength, Rng& rng);
    SimpleEvo(std::istream& in, Rng& rng);
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;
    void save(std::ostream& out) const;
    static std::pair<SimpleEvo, unsigned> evolve(
        unsigned mu, unsigned lambda, double init_mutation_strength, ScoringFunc scoring_func, unsigned iterations,
        Rng& rng
    );
};

#endif