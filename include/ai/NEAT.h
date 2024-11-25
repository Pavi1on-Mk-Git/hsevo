#ifndef POPULATION_H
#define POPULATION_H

#include "ai/Genome.h"
#include "ai/NEATConfig.h"
#include "ai/Network.hpp"

class NEAT
{
private:
    using Species = std::vector<unsigned>;

    std::vector<Genome> population_;
    std::vector<Network> networks_;
    std::vector<unsigned> scores_;
    std::vector<double> adjusted_scores_;
    std::vector<unsigned> genome_to_species_;

    std::vector<Genome> representatives_;
    std::vector<Species> species_;
    std::vector<double> species_score_sums_;
    std::vector<unsigned> species_bounds_;

    NEATConfig config;

    void speciate(double similarity_threshold, double excess_coeff, double disjoint_coeff, double weight_coeff);
    void adjust_scores();
    void sort_species();
    void calculate_species_bounds();
    std::optional<Genome> crossover(
        const Species& species, unsigned bound, double crossover_prob, double interspecies_mating_prob,
        double inherit_connection_disabled_prob
    );
    void offspring(
        double weight_mutation_prob, double add_node_mutation_prob, double add_connection_prob,
        double weight_perturbation_prob, double mutation_strength, double crossover_prob,
        double interspecies_mating_prob, double inherit_connection_disabled_prob
    );
    void cleanup_species();
    void get_networks(ActivationFunc activation);
public:
    NEAT(const NEATConfig& config);
    const std::vector<Network>& networks() const;
    std::pair<Network, unsigned> assign_scores(const std::vector<unsigned>& scores);
    void epoch();
};

#endif