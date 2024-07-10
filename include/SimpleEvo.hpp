#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <random>

#include "Board.h"
#include "Rng.h"
#include "decklists.h"

template <unsigned InSize>
class SimpleEvo
{
private:
    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;
    std::array<double, InSize> weights_;
    std::array<double, InSize> mutation_strengths_;
public:
    SimpleEvo(double init_mutation_strength)
    {
        std::generate(weights_.begin(), weights_.end(), []() {
            return Rng::instance()->uniform_real(MIN_WEIGHT, MAX_WEIGHT);
        });
        std::fill(mutation_strengths_.begin(), mutation_strengths_.end(), init_mutation_strength);
    }

    double score_vec(const std::array<double, InSize>& input_vec) const
    {
        double score = 0.;
        for(unsigned i = 0; i < InSize; ++i)
            score += weights_.at(i) * input_vec.at(i);
        return score;
    }

    void mutate()
    {
        auto random_evo_coeff_a = Rng::instance()->uniform_real(), random_evo_coeff_b = Rng::instance()->uniform_real();

        std::transform(
            mutation_strengths_.begin(), mutation_strengths_.end(), mutation_strengths_.begin(),
            [&](double strength) {
                return std::max(
                    strength * std::exp(
                                   random_evo_coeff_a / std::sqrt(2. * std::sqrt(InSize)) +
                                   random_evo_coeff_b / std::sqrt(2. * InSize)
                               ),
                    1e-5
                );
            }
        );

        for(unsigned weight_index = 0; weight_index < InSize; ++weight_index)
        {
            weights_.at(weight_index) = std::clamp(
                weights_.at(weight_index) + Rng::instance()->uniform_real(0, mutation_strengths_.at(weight_index)), 0.,
                1.
            );
        }
    }

    static std::vector<SimpleEvo<InSize>> init_population(unsigned population_size, double init_mutation_strength)
    {
        std::vector<SimpleEvo<InSize>> population;
        population.reserve(population_size);
        std::generate_n(std::back_inserter(population), population_size, [&]() {
            return SimpleEvo<InSize>(init_mutation_strength);
        });
        return population;
    }

    static std::vector<std::pair<SimpleEvo<InSize>, unsigned>> mutate_population(
        const std::vector<SimpleEvo<InSize>>& population, unsigned mutants_size,
        std::function<std::vector<unsigned>(std::vector<SimpleEvo<InSize>>)> scoring_func
    )
    {
        std::vector<SimpleEvo<InSize>> mutants;
        mutants.reserve(mutants_size + population.size());
        for(unsigned mutant_id = 0; mutant_id < mutants_size; ++mutant_id)
        {
            unsigned to_mutate = Rng::instance()->uniform_int(0, population.size() - 1);
            auto mutant = population.at(to_mutate);
            mutant.mutate();
            mutants.push_back(mutant);
        }

        std::move(population.begin(), population.end(), mutants.end());

        auto scores = scoring_func(mutants);

        std::vector<std::pair<SimpleEvo<InSize>, unsigned>> mutants_with_scores;

        std::transform(
            mutants.begin(), mutants.end(), scores.begin(), std::back_inserter(mutants_with_scores),
            [](const auto& member, unsigned score) { return std::make_pair(member, score); }
        );

        return mutants_with_scores;
    }

    static std::pair<SimpleEvo<InSize>, unsigned> evolve(
        unsigned mu, unsigned lambda, double init_mutation_strength,
        std::function<std::vector<unsigned>(std::vector<SimpleEvo<InSize>>)> scoring_func, unsigned iterations
    )
    {
        std::vector<SimpleEvo<InSize>> population;
        population.reserve(mu);
        population = init_population(mu, init_mutation_strength);

        auto best_member = std::make_pair(SimpleEvo<InSize>(init_mutation_strength), 0);

        for(unsigned iteration = 0; iteration < iterations; ++iteration)
        {
            auto mutants_with_scores = mutate_population(population, lambda, scoring_func);
            std::nth_element(
                mutants_with_scores.begin(), mutants_with_scores.begin() + mu, mutants_with_scores.end(),
                [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
            );

            std::transform(
                mutants_with_scores.begin(), mutants_with_scores.begin() + mu, population.begin(),
                [](const auto& member_with_score) { return member_with_score.first; }
            );

            best_member = *std::max_element(
                mutants_with_scores.begin(), mutants_with_scores.begin() + mu,
                [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
            );
        }

        return best_member;
    }
};

std::vector<unsigned int> score_member(
    const std::vector<SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>>& population, const DeckList& decklist
);

#endif