#include "ai/NEAT.h"

#include <algorithm>
#include <cmath>
#include <numeric>

#include "utils/Rng.h"

NEAT::NEAT(unsigned size)
{
    population_.reserve(size);
    for(unsigned i = 0; i < size; ++i)
        population_.push_back(Genome());

    networks_.reserve(size);
    scores_.reserve(size);
    adjusted_scores_.resize(size);
    genome_to_species_.resize(size);
}

void NEAT::get_networks(ActivationFunc activation)
{
    networks_.clear();

    std::ranges::transform(population_, std::back_inserter(networks_), [&activation](const auto& genome) {
        return Network(genome, activation);
    });
}

void NEAT::score_networks(ScoringFunc scoring_func)
{
    scores_ = scoring_func(networks_);

    auto best_score_it = std::ranges::max_element(scores_);
    best_network_ = {networks_.at(best_score_it - scores_.begin()), *best_score_it};
}

void NEAT::speciate(double similarity_threshold, double excess_coeff, double disjoint_coeff, double weight_coeff)
{
    for(unsigned genome_id = 0; genome_id < population_.size(); ++genome_id)
    {
        const auto& genome = population_.at(genome_id);
        bool found_species = false;

        for(unsigned species_id = 0; species_id < representatives_.size(); ++species_id)
        {
            const auto& representative = representatives_.at(species_id);
            if(genome.similarity(representative, excess_coeff, disjoint_coeff, weight_coeff) < similarity_threshold)
            {
                species_.at(species_id).push_back(genome_id);
                genome_to_species_.at(genome_id) = species_id;
                found_species = true;
                break;
            }
        }

        if(!found_species)
        {
            representatives_.push_back(genome);
            genome_to_species_.at(genome_id) = species_.size();
            species_.emplace_back(1, genome_id);
            species_score_sums_.push_back(0.);
        }
    }
}

void NEAT::adjust_scores()
{
    for(unsigned genome_id = 0; genome_id < population_.size(); ++genome_id)
    {
        const unsigned species_id = genome_to_species_.at(genome_id);
        const double adjusted_score = scores_.at(genome_id) / species_.at(species_id).size();

        adjusted_scores_.at(genome_id) = adjusted_score;
        species_score_sums_.at(species_id) += adjusted_score;
    }
}

void NEAT::sort_species()
{
    for(auto& species: species_)
        std::ranges::sort(species, [this](unsigned fst, unsigned snd) {
            return adjusted_scores_.at(fst) < adjusted_scores_.at(snd);
        });
}

void NEAT::calculate_species_bounds()
{
    species_bounds_.resize(species_.size());

    const double total_score = std::accumulate(species_score_sums_.begin(), species_score_sums_.end(), 0.);

    for(unsigned species_id = 0; species_id < species_.size(); ++species_id)
        species_bounds_.at(species_id
        ) = std::ceil(species_score_sums_.at(species_id) * species_.at(species_id).size() / total_score);
}

std::optional<Genome> NEAT::crossover(
    const Species& species, unsigned bound, double crossover_prob, double interspecies_mating_prob,
    double inherit_connection_disabled_prob
)
{
    auto& rng = Rng::instance();

    if(rng.uniform_real() < crossover_prob && bound > 0)
    {
        const unsigned first_parent_id = species.at(rng.uniform_int(0, bound - 1));
        const Genome& first_parent = population_.at(first_parent_id);
        const double first_parent_score = adjusted_scores_.at(first_parent_id);

        if(rng.uniform_real() < interspecies_mating_prob)
        {
            std::vector<unsigned> alive_species{};
            for(unsigned alive_species_id = 0; alive_species_id < species_.size(); ++alive_species_id)
                if(!species_.at(alive_species_id).empty())
                    alive_species.push_back(alive_species_id);

            const unsigned second_parent_species_id = alive_species.at(rng.uniform_int(0, alive_species.size() - 1));

            const Species& second_parent_species = species_.at(second_parent_species_id);
            const unsigned second_bound = species_bounds_.at(second_parent_species_id);
            const unsigned second_parent_id = second_parent_species.at(rng.uniform_int(0, second_bound - 1));
            const Genome& second_parent = population_.at(second_parent_id);
            const double second_parent_score = adjusted_scores_.at(second_parent_id);

            return Genome::crossover(
                first_parent, first_parent_score, second_parent, second_parent_score, inherit_connection_disabled_prob
            );
        }
        else
        {
            const unsigned second_parent_id = species.at(rng.uniform_int(0, bound - 1));
            const Genome& second_parent = population_.at(second_parent_id);
            const double second_parent_score = adjusted_scores_.at(second_parent_id);

            return Genome::crossover(
                first_parent, first_parent_score, second_parent, second_parent_score, inherit_connection_disabled_prob
            );
        }
    }
    return std::nullopt;
}

void NEAT::offspring(
    double weight_mutation_prob, double add_node_mutation_prob, double add_connection_prob,
    double weight_perturbation_prob, double mutation_strength, double crossover_prob, double interspecies_mating_prob,
    double inherit_connection_disabled_prob
)
{
    for(unsigned species_id = 0; species_id < species_.size(); ++species_id)
    {
        const Species& species = species_.at(species_id);
        if(species.empty())
            continue;

        const unsigned bound = species_bounds_.at(species_id);

        for(unsigned old_genome_id = 0; old_genome_id < bound; ++old_genome_id)
            population_.at(species[old_genome_id])
                .mutate(
                    weight_mutation_prob, add_node_mutation_prob, add_connection_prob, weight_perturbation_prob,
                    mutation_strength
                );

        for(unsigned new_genome_id = bound; new_genome_id < species.size(); ++new_genome_id)
        {
            Genome& to_replace = population_.at(species[new_genome_id]);

            auto new_genome = crossover(
                species, bound, crossover_prob, interspecies_mating_prob, inherit_connection_disabled_prob
            );

            if(new_genome)
                to_replace = *new_genome;

            to_replace.mutate(
                weight_mutation_prob, add_node_mutation_prob, add_connection_prob, weight_perturbation_prob,
                mutation_strength
            );
        }
    }
}

void NEAT::cleanup_species()
{
    std::vector<Genome> clean_representatives;
    clean_representatives.reserve(species_.size());

    for(unsigned species_id = 0; species_id < species_.size(); ++species_id)
    {
        const Species& species = species_.at(species_id);
        unsigned kept_count = species_bounds_.at(species_id);

        if(!species.empty() && kept_count > 0)
            clean_representatives.push_back(population_.at(species[Rng::instance().uniform_int(0, kept_count - 1)]));
    }

    species_.clear();
    species_.resize(clean_representatives.size());
    representatives_ = std::move(clean_representatives);

    species_score_sums_.clear();
    species_score_sums_.resize(species_.size(), 0.);
}

std::pair<Network, unsigned> NEAT::evolve(const NEATConfig& config)
{
    NEAT population(config.population_size);

    for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
    {
        population.get_networks(config.activation);
        population.score_networks(config.scoring_func);
        population.speciate(config.weight_coeff, config.excess_coeff, config.disjoint_coeff, config.weight_coeff);
        population.adjust_scores();
        population.sort_species();
        population.calculate_species_bounds();
        population.offspring(
            config.weight_mutation_prob, config.add_node_mutation_prob, config.add_connection_prob,
            config.weight_perturbation_prob, config.mutation_strength, config.crossover_prob,
            config.interspecies_mating_prob, config.inherit_connection_disabled_prob
        );
        population.cleanup_species();
    }

    return *population.best_network_;
}