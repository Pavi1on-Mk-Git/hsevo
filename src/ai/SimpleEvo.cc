#include "ai/SimpleEvo.h"

#include <algorithm>

SimpleEvo::SimpleEvo(const EvoConfig& config, Rng& rng): rng_(rng), config_(config)
{
    population_.reserve(config_.mu);
    std::generate_n(std::back_inserter(population_), config_.mu, [&]() {
        return EvoSpecimen(config_.init_mutation_strength, rng);
    });
}

void SimpleEvo::mutate()
{
    std::vector<EvoSpecimen> mutants;
    mutants.reserve(config_.mu + config_.lambda);

    for(unsigned mutant_id = 0; mutant_id < config_.lambda; ++mutant_id)
    {
        const unsigned to_mutate = rng_.uniform_int(0, config_.mu - 1);
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
    mutants_with_scores.reserve(config_.mu + config_.lambda);

    std::ranges::transform(
        population_, scores_, std::back_inserter(mutants_with_scores),
        [](const auto& mutant, const auto& score) { return std::make_pair(mutant, score); }
    );

    std::ranges::nth_element(
        mutants_with_scores.begin(), mutants_with_scores.begin() + config_.mu, mutants_with_scores.end(),
        [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
    );

    population_.clear();
    scores_.clear();

    std::ranges::transform(
        mutants_with_scores.begin(), mutants_with_scores.begin() + config_.mu, std::back_inserter(population_),
        [](const auto& member_with_score) { return member_with_score.first; }
    );

    mutate();
}
