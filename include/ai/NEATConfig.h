#ifndef NEAT_CONFIG_H
#define NEAT_CONFIG_H

#include <functional>

#include "ai/ActivationFunc.hpp"

struct Network;

using ScoringFunc = std::function<std::vector<unsigned>(std::vector<Network>)>;

struct NEATConfig
{
    unsigned population_size;
    unsigned iterations;
    ScoringFunc scoring_func;
    ActivationFunc activation;
    double similarity_threshold;
    double excess_coeff;
    double disjoint_coeff;
    double weight_coeff;
    double weight_mutation_prob;
    double add_node_mutation_prob;
    double add_connection_prob;
    double weight_perturbation_prob;
    double mutation_strength;
    double crossover_prob;
    double interspecies_mating_prob;
    double inherit_connection_disabled_prob;
};

#endif