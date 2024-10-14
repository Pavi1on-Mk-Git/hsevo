#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>
#include <iostream>

#include "ai/GameStateInput.h"

class SimpleEvo
{
private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & weights_ & mutation_strengths_;
    }

    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;
    std::array<double, GameStateInput::INPUT_SIZE> weights_;
    std::array<double, GameStateInput::INPUT_SIZE> mutation_strengths_;

    using ScoringFunc = std::function<std::vector<unsigned>(std::vector<SimpleEvo>)>;

    void mutate();
    static auto init_population(unsigned population_size, double init_mutation_strength);

    static auto mutate_population(
        const std::vector<SimpleEvo>& population, unsigned mutants_size, ScoringFunc scoring_func
    );
public:
    SimpleEvo(double init_mutation_strength);
    SimpleEvo(std::istream& in);
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;
    void save(std::ostream& out) const;
    static std::pair<SimpleEvo, unsigned> evolve(
        unsigned mu, unsigned lambda, double init_mutation_strength, ScoringFunc scoring_func, unsigned iterations
    );
};

#endif