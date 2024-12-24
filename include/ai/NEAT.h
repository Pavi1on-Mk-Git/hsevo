#ifndef NEAT_H
#define NEAT_H

#include "ai/Genome.h"
#include "ai/NEATConfig.h"
#include "ai/Network.hpp"

/**
 * Neuroevolution of Augmenting Topologies algorithm
 */
class NEAT
{
private:
    using Species = std::vector<unsigned>;

    /**
     * Population of genomes
     */
    std::vector<Genome> population_;

    /**
     * Neural networks created from members of the population
     */
    std::vector<Network> networks_;

    /**
     * Scores of the population
     */
    std::vector<unsigned> scores_;

    /**
     * Scores of the population adjusted by size of the genome's species
     */
    std::vector<double> adjusted_scores_;

    /**
     * Mapping of genome to its species
     */
    std::vector<unsigned> genome_to_species_;

    /**
     * Representatives of each species
     */
    std::vector<Genome> representatives_;

    /**
     * Species of genomes
     */
    std::vector<Species> species_;

    /**
     * Sums of species' scores
     */
    std::vector<double> species_score_sums_;

    /**
     * Bounds on species' sizes computed using their scores
     */
    std::vector<unsigned> species_bounds_;

    /**
     * Algorithm configuration
     */
    const NEATConfig config_;

    /**
     * Source of randomness
     */
    Rng rng_;

    /**
     * Split the population into species based on similarity
     */
    void speciate();

    /**
     * Compute the adjusted scores of genomes based on the size of their species
     */
    void adjust_scores();

    /**
     * Sort the species by their adjusted scores
     */
    void sort_species();

    /**
     * Calculate the bound of each species based on its adjusted score
     */
    void calculate_species_bounds();

    /**
     * Crossover two randomly selected genomes from the selected species
     *
     * @param species Species two select two genomes from
     * @param bound Bound of the selected species
     * @return Genome resulting from crossover or `std::nullopt` if a crossover didn't happen
     */
    std::optional<Genome> crossover(const Species& species, unsigned bound);

    /**
     * Replace the population with its offspring
     */
    void offspring();

    /**
     * Cleanup species-related data inside the algorithm
     */
    void cleanup_species();

    /**
     * Create neural networks from the population and provided activation function
     *
     * @param activation Activation function to use
     */
    void get_networks();
public:
    /**
     * Construct an instance of the NEAT algorithm using the provided configuration
     *
     * @param config Configuration to use
     * @param rng Source of randomness
     */
    NEAT(const NEATConfig& config, Rng& rng_);

    /**
     * Return neural networks for the current population
     *
     * @return Vector of neural networks
     */
    const std::vector<Network>& get_population() const;

    /**
     * Assign scores to current population
     *
     * @param scores Scores to assign
     * @return The best network along with its score
     */
    std::pair<Network, unsigned> assign_scores(const std::vector<unsigned>& scores);

    /**
     * Advance the algorithm by a single epoch
     *
     * An epoch consists of:
     * - splitting the population into species
     * - sorting the population using their adjusted scores
     * - replacing the population with its offspring
     * - creating neural networks from the resulting population
     */
    void epoch();
};

#endif