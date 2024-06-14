#ifndef SIMPLE_EVO_H
#define SIMPLE_EVO_H

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <random>

#include "Board.h"
#include "decklists.h"

template <unsigned int InSize>
class SimpleEvo
{
private:
    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;
    std::reference_wrapper<std::ranlux24_base> _random_engine;
    std::array<double, InSize> _weights;
    std::array<double, InSize> _mutation_strengths;
public:
    SimpleEvo(double init_mutation_strength, std::ranlux24_base& random_engine): _random_engine(random_engine)
    {
        std::uniform_real_distribution random_uniform(MIN_WEIGHT, MAX_WEIGHT);
        std::generate(_weights.begin(), _weights.end(), [&random_uniform, this]() {
            return random_uniform(_random_engine.get());
        });
        std::fill(_mutation_strengths.begin(), _mutation_strengths.end(), init_mutation_strength);
    }

    double score_vec(const std::array<double, InSize>& input_vec) const
    {
        double score = 0.;
        for(auto i = 0u; i < InSize; ++i)
            score += _weights.at(i) * input_vec.at(i);
        return score;
    }

    void mutate()
    {
        std::uniform_real_distribution random_uniform(0., 1.);
        std::transform(
            _mutation_strengths.begin(), _mutation_strengths.end(), _mutation_strengths.begin(),
            [&](const auto& strength) {
                return std::max(
                    strength * std::exp(
                                   random_uniform(_random_engine.get()) / std::sqrt(2. * std::sqrt(InSize)) +
                                   random_uniform(_random_engine.get()) / std::sqrt(2. * InSize)
                               ),
                    1e-5
                );
            }
        );

        for(auto weight_index = 0u; weight_index < InSize; ++weight_index)
        {
            std::uniform_real_distribution random_uniform_mutating(0., _mutation_strengths.at(weight_index));
            _weights.at(weight_index
            ) = std::clamp(_weights.at(weight_index) + random_uniform_mutating(_random_engine.get()), 0., 1.);
        }
    }

    static std::vector<SimpleEvo<InSize>> init_population(
        unsigned int population_size, double init_mutation_strength, std::ranlux24_base& random_engine
    )
    {
        std::vector<SimpleEvo<InSize>> population;
        population.reserve(population_size);
        std::generate_n(std::back_inserter(population), population_size, [&]() {
            return SimpleEvo<InSize>(init_mutation_strength, random_engine);
        });
        return population;
    }

    static std::vector<std::pair<SimpleEvo<InSize>, unsigned int>> mutate_population(
        const std::vector<SimpleEvo<InSize>>& population, unsigned int mutants_size,
        std::function<std::vector<unsigned int>(std::vector<SimpleEvo<InSize>>)> scoring_func,
        std::ranlux24_base& random_engine
    )
    {
        std::vector<SimpleEvo<InSize>> mutants;
        mutants.reserve(mutants_size + population.size());
        std::uniform_int_distribution<unsigned int> random_uniform(0, population.size() - 1);
        for(auto mutant_id = 0u; mutant_id < mutants_size; ++mutant_id)
        {
            auto to_mutate = random_uniform(random_engine);
            auto mutant = population.at(to_mutate);
            mutant.mutate();
            mutants.push_back(mutant);
        }

        std::move(population.begin(), population.end(), mutants.end());

        auto scores = scoring_func(mutants);

        std::vector<std::pair<SimpleEvo<InSize>, unsigned int>> mutants_with_scores;

        std::transform(
            mutants.begin(), mutants.end(), scores.begin(), std::back_inserter(mutants_with_scores),
            [](const auto& member, const auto& score) { return std::make_pair(member, score); }
        );

        return mutants_with_scores;
    }

    static std::pair<SimpleEvo<InSize>, unsigned int> evolve(
        unsigned int mu, unsigned int lambda, double init_mutation_strength,
        std::function<std::vector<unsigned int>(std::vector<SimpleEvo<InSize>>)> scoring_func, unsigned int iterations,
        std::ranlux24_base& random_engine
    )
    {
        std::vector<SimpleEvo<InSize>> population;
        population.reserve(mu);
        population = init_population(mu, init_mutation_strength, random_engine);

        auto best_member = std::make_pair(SimpleEvo<InSize>(init_mutation_strength, random_engine), 0);

        for(auto iteration = 0u; iteration < iterations; ++iteration)
        {
            auto mutants_with_scores = mutate_population(population, lambda, scoring_func, random_engine);
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
    const std::vector<SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>>& population, const DeckList& decklist,
    std::ranlux24_base& random_engine
);

#endif