#include "ai/SimpleEvo.h"

#include <algorithm>

SimpleEvo::SimpleEvo(unsigned mu, unsigned lambda, double init_mutation_strength, Rng& rng):
    rng_(rng), mu_(mu), lambda_(lambda)
{
    population_.reserve(mu);
    std::generate_n(std::back_inserter(population_), mu, [&]() { return EvoSpecimen(init_mutation_strength, rng); });
}

void SimpleEvo::mutate()
{
    std::vector<EvoSpecimen> mutants;
    mutants.reserve(mu_ + lambda_);

    for(unsigned mutant_id = 0; mutant_id < lambda_; ++mutant_id)
    {
        const unsigned to_mutate = rng_.uniform_int(0, mu_ - 1);
        auto mutant = population_.at(to_mutate);
        mutant.mutate();
        mutants.push_back(mutant);
    }

    std::ranges::move(mutants, std::back_inserter(population_));
}

const std::vector<EvoSpecimen>& SimpleEvo::get_population() const
{
    return population_;
}

std::pair<EvoSpecimen, unsigned> SimpleEvo::assign_scores(const std::vector<unsigned>& scores)
{
    scores_ = scores;

    auto best_score_it = std::ranges::max_element(scores_);
    return {population_.at(best_score_it - scores_.begin()), *best_score_it};
}

void SimpleEvo::epoch()
{
    std::vector<std::pair<EvoSpecimen, unsigned>> mutants_with_scores;
    mutants_with_scores.reserve(mu_ + lambda_);

    std::ranges::transform(
        population_, scores_, std::back_inserter(mutants_with_scores),
        [](const auto& mutant, const auto& score) { return std::make_pair(mutant, score); }
    );

    std::ranges::nth_element(
        mutants_with_scores.begin(), mutants_with_scores.begin() + mu_, mutants_with_scores.end(),
        [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
    );

    population_.clear();
    scores_.clear();

    std::ranges::transform(
        mutants_with_scores.begin(), mutants_with_scores.begin() + mu_, std::back_inserter(population_),
        [](const auto& member_with_score) { return member_with_score.first; }
    );

    mutate();
}
