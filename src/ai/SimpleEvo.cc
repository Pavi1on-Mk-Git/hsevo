#include "ai/SimpleEvo.h"

#include <cmath>

#include "utils/Rng.h"

void SimpleEvo::mutate()
{
    double random_evo_coeff_a = Rng::instance()->normal(), random_evo_coeff_b = Rng::instance()->normal();

    std::transform(
        mutation_strengths_.begin(), mutation_strengths_.end(), mutation_strengths_.begin(),
        [&](double strength) {
            return std::max(
                strength * std::exp(
                               random_evo_coeff_a / std::sqrt(2. * std::sqrt(GameStateInput::INPUT_SIZE)) +
                               random_evo_coeff_b / std::sqrt(2. * GameStateInput::INPUT_SIZE)
                           ),
                1e-5
            );
        }
    );

    std::transform(
        weights_.begin(), weights_.end(), mutation_strengths_.begin(), weights_.begin(),
        [](double weight, double strength) {
            return std::clamp(weight + Rng::instance()->normal(0., strength), MIN_WEIGHT, MAX_WEIGHT);
        }
    );
}

auto SimpleEvo::init_population(unsigned population_size, double init_mutation_strength)
{
    std::vector<SimpleEvo> population;
    population.reserve(population_size);
    std::generate_n(std::back_inserter(population), population_size, [&]() {
        return SimpleEvo(init_mutation_strength);
    });
    return population;
}

auto SimpleEvo::mutate_population(
    const std::vector<SimpleEvo>& population, unsigned mutants_size, ScoringFunc scoring_func
)
{
    std::vector<SimpleEvo> mutants;
    mutants.reserve(mutants_size + population.size());

    for(unsigned mutant_id = 0; mutant_id < mutants_size; ++mutant_id)
    {
        const unsigned to_mutate = Rng::instance()->uniform_int(0, population.size() - 1);
        auto mutant = population.at(to_mutate);
        mutant.mutate();
        mutants.push_back(mutant);
    }

    std::move(population.begin(), population.end(), mutants.end());

    auto scores = scoring_func(mutants);

    std::vector<std::pair<SimpleEvo, unsigned>> mutants_with_scores;
    mutants_with_scores.reserve(mutants.size());

    std::transform(
        mutants.begin(), mutants.end(), scores.begin(), std::back_inserter(mutants_with_scores),
        [](const auto& member, unsigned score) { return std::make_pair(member, score); }
    );

    return mutants_with_scores;
}

SimpleEvo::SimpleEvo(double init_mutation_strength)
{
    std::generate(weights_.begin(), weights_.end(), []() {
        return Rng::instance()->uniform_real(MIN_WEIGHT, MAX_WEIGHT);
    });
    std::fill(mutation_strengths_.begin(), mutation_strengths_.end(), init_mutation_strength);
}

double SimpleEvo::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    double score = 0.;
    for(unsigned i = 0; i < GameStateInput::INPUT_SIZE; ++i)
        score += weights_.at(i) * input_vec.at(i);
    return score;
}

std::pair<SimpleEvo, unsigned> SimpleEvo::evolve(
    unsigned mu, unsigned lambda, double init_mutation_strength, ScoringFunc scoring_func, unsigned iterations
)
{
    auto population = init_population(mu, init_mutation_strength);

    auto best_member = std::make_pair(SimpleEvo(init_mutation_strength), 0);

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