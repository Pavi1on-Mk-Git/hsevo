#include "ai/NEAT.h"

#include <algorithm>
#include <cmath>
#include <ranges>

#include "utils/Rng.h"

void NEAT::speciate(double similarity_threshold, double excess_coeff, double disjoint_coeff, double weight_coeff)
{
    for(auto [genome_id, genome, genome_species]: std::views::zip(std::views::iota(0), population_, genome_to_species_))
    {
        bool found_species = false;
        for(auto [species_id, species, representative]:
            std::views::zip(std::views::iota(0), species_, representatives_))
        {
            if(genome.similarity(representative, excess_coeff, disjoint_coeff, weight_coeff) < similarity_threshold)
            {
                species.push_back(genome_id);
                genome_species = species_id;
                found_species = true;
                break;
            }
        }

        if(!found_species)
        {
            representatives_.push_back(genome);
            genome_species = species_.size();
            species_.emplace_back(1, genome_id);
            species_score_sums_.push_back(0.);
        }
    }
}

void NEAT::adjust_scores()
{
    for(auto [genome_species, score, prev_adjusted_score]:
        std::views::zip(genome_to_species_, scores_, adjusted_scores_))
    {
        const double adjusted_score = score / species_.at(genome_species).size();

        prev_adjusted_score = adjusted_score;
        species_score_sums_.at(genome_species) += adjusted_score;
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
    species_bounds_.reserve(species_.size());

    const double total_score = *std::ranges::fold_left_first(species_score_sums_, std::plus{});

    for(auto [score_sum, species]: std::views::zip(species_score_sums_, species_))
        species_bounds_.push_back(std::ceil(score_sum * species.size() / total_score));
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
            std::vector<unsigned> alive_species;
            for(auto [alive_species_id, species]: std::views::enumerate(species_))
                if(!species.empty())
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
    for(auto [species, bound]: std::views::zip(species_, species_bounds_))
    {
        if(species.empty())
            continue;

        for(unsigned old_genome_id: species | std::views::take(bound))
            population_.at(old_genome_id)
                .mutate(
                    weight_mutation_prob, add_node_mutation_prob, add_connection_prob, weight_perturbation_prob,
                    mutation_strength
                );

        for(unsigned new_genome_id: species | std::views::drop(bound))
        {
            Genome& to_replace = population_.at(new_genome_id);

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

    for(auto [species, kept_count]: std::views::zip(species_, species_bounds_))
        if(!species.empty() && kept_count > 0)
            clean_representatives.push_back(population_.at(species.at(Rng::instance().uniform_int(0, kept_count - 1))));

    species_.clear();
    species_.resize(clean_representatives.size());
    representatives_ = std::move(clean_representatives);

    species_score_sums_.clear();
    species_score_sums_.resize(species_.size(), 0.);
}

NEAT::NEAT(const NEATConfig& config)
{
    population_.reserve(config.population_size);
    std::ranges::generate_n(std::back_inserter(population_), config.population_size, [] { return Genome(); });
    networks_.reserve(config.population_size);
    scores_.reserve(config.population_size);
    adjusted_scores_.resize(config.population_size);
    genome_to_species_.resize(config.population_size);

    cleanup_species();
    get_networks(config.activation);
}

void NEAT::get_networks(ActivationFunc activation)
{
    networks_.clear();

    std::ranges::transform(population_, std::back_inserter(networks_), [&activation](const auto& genome) {
        return Network(genome, activation);
    });
}

const std::vector<Network>& NEAT::networks() const
{
    return networks_;
}

std::pair<Network, unsigned> NEAT::assign_scores(const std::vector<unsigned>& scores)
{
    scores_ = scores;

    auto best_score_it = std::ranges::max_element(scores_);
    return {networks_.at(best_score_it - scores_.begin()), *best_score_it};
}

void NEAT::epoch()
{
    speciate(config.weight_coeff, config.excess_coeff, config.disjoint_coeff, config.weight_coeff);
    adjust_scores();
    sort_species();
    calculate_species_bounds();
    offspring(
        config.weight_mutation_prob, config.add_node_mutation_prob, config.add_connection_prob,
        config.weight_perturbation_prob, config.mutation_strength, config.crossover_prob,
        config.interspecies_mating_prob, config.inherit_connection_disabled_prob
    );
    cleanup_species();
    get_networks(config.activation);
}
