#include "ai/NEAT.h"

#include <algorithm>

NEAT::NEAT(unsigned size)
{
    population_.reserve(size);
    for(unsigned i = 0; i < size; ++i)
        population_.push_back(Genome());

    networks_.reserve(size);
    scores_.reserve(size);
    adjusted_scores_.reserve(size);
    genome_to_species.reserve(size);
}

void NEAT::get_networks(ActivationFunc activation)
{
    networks_.clear();

    std::transform(
        population_.begin(), population_.end(), std::back_inserter(networks_),
        [&activation](const auto& genome) { return Network(genome, activation); }
    );
}

void NEAT::score_networks(ScoringFunc scoring_func)
{
    scores_ = scoring_func(networks_);

    auto best_score_it = std::max_element(scores_.begin(), scores_.end());
    best_network_ = {networks_.at(best_score_it - scores_.begin()), *best_score_it};
}

std::pair<Network, unsigned> NEAT::evolve(const NEATConfig& config)
{
    NEAT population(config.population_size);

    for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
    {
        population.get_networks(config.activation);
        population.score_networks(config.scoring_func);
    }

    return *population.best_network_;
}