#ifndef POPULATION_H
#define POPULATION_H

#include "ai/Genome.h"
#include "ai/NEATConfig.h"
#include "ai/Network.h"

class NEAT
{
private:
    using Species = std::vector<unsigned>;

    std::vector<Genome> population_;
    std::vector<Network> networks_;
    std::optional<std::pair<Network, unsigned>> best_network_;
    std::vector<unsigned> scores_;
    std::vector<double> adjusted_scores_;
    std::vector<unsigned> genome_to_species;

    std::vector<std::reference_wrapper<Genome>> representatives_;
    std::vector<Species> species_;
    std::vector<double> species_score_sums_;
    std::vector<double> species_score_max_;
    std::vector<unsigned> species_stagnant_generations_;
    std::vector<unsigned> species_bounds_;

    NEAT(unsigned size);
    void get_networks(ActivationFunc activation);
    void score_networks(ScoringFunc scoring_func);
public:
    static std::pair<Network, unsigned> evolve(const NEATConfig& config);
};

#endif