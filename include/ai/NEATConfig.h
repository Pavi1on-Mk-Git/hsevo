#ifndef NEAT_CONFIG_H
#define NEAT_CONFIG_H

#include <functional>

#include "ai/ActivationFunc.hpp"

/**
 * Configuration for NEAT algorithm
 */
struct NEATConfig
{
    /**
     * Size of the population
     */
    unsigned population_size;

    /**
     * Activation function used in neural networks
     */
    ActivationFunc activation;

    /**
     * Genome similarity threshold
     */
    double similarity_threshold;

    /**
     * Coefficient used to compute the part of similarity related to excess genes
     */
    double excess_coeff;

    /**
     * Coefficient used to compute the part of similarity related to disjoint genes
     */
    double disjoint_coeff;

    /**
     * Coefficient used to compute the part of similarity related to genome weight difference
     */
    double weight_coeff;

    /**
     * Weight mutation probability
     */
    double weight_mutation_prob;

    /**
     * Add node mutation probability
     */
    double add_node_mutation_prob;

    /**
     * Add connection mutation probability
     */
    double add_connection_prob;

    /**
     * Weight perturbation probability
     */
    double weight_perturbation_prob;

    /**
     * Strength of the weight perturbation
     */
    double mutation_strength;

    /**
     * Crossover probability
     */
    double crossover_prob;

    /**
     * Probability of inheriting a connection in disabled state during crossover
     */
    double inherit_connection_disabled_prob;

    /**
     * Human-readable name of the configuration
     * @return Name of the configuration
     */
    std::string name() const;

    /**
     * Get default configuration
     * @return Configuration filled with default values
     */
    static NEATConfig default_config();
};

#endif