#ifndef GENOME_HPP
#define GENOME_HPP

#include <optional>
#include <vector>

#include "ai/Connection.h"
#include "utils/Rng.h"

using ConnectionHash = std::uint64_t;

/**
 * Genome representing the structure of a neural network
 */
class Genome
{
private:
    /**
     * Source of randomness
     */
    std::reference_wrapper<Rng> rng_;

    /**
     * Reverse mapping of a node to its layer
     */
    std::vector<unsigned> node_to_layer_;

    /**
     * Compute the hash of a connection between two nodes
     *
     * @param from Id of the source node
     * @param to Id of the target node
     * @return Unique hash of the connection
     */
    static ConnectionHash get_connection_hash(NodeId from, NodeId to);

    /**
     * Find the connection between two nodes
     *
     * @param from Id of the source node
     * @param to Id of the target node
     * @return The connection if it exists, `std::nullopt` otherwise
     */
    std::optional<Connection> find_connection(NodeId from, NodeId to);

    /**
     * Add a connection between two nodes to the genome
     *
     * Created connection will be enabled
     *
     * @param from Id of the source node
     * @param to Id of the target node
     * @param weight Weight of the connection
     */
    void add_connection(NodeId from, NodeId to, double weight);

    /**
     * Add a node to the specified layer
     *
     * @param layer Id of the layer
     */
    void add_node_to_layer(unsigned layer);

    /**
     * Mutate the weight of the provided connection
     *
     * @param connection Connection to mutate
     * @param weight_perturbation_prob Probability of weight perturbation
     * @param mutation_strength Strength of the weight perturbation
     */
    void mutate_weight(Connection& connection, double weight_perturbation_prob, double mutation_strength);

    /**
     * Mutate the genome by adding a new node by splitting a randomly chosen connection
     */
    void mutate_add_node();

    /**
     * Mutate the genome by adding a connection between two randomly selected nodes
     *
     * If the connection already exists it is instead disabled
     */
    void mutate_add_connection();
public:
    /**
     * Id of the next node to be created
     */
    NodeId next_node_id;

    /**
     * Mapping of a layer to a vector of nodes present in the layer
     */
    std::vector<std::pair<unsigned, std::vector<NodeId>>> layers;

    /**
     * Mapping of connection hashes to connections
     */
    std::vector<std::pair<ConnectionHash, Connection>> connections;

    /**
     * Construct a random Genome
     *
     * @param rng Source of randomness
     */
    Genome(Rng& rng);

    /**
     * Construct a Genome from existing parameters
     *
     * @param next_node_id Id of the next node
     * @param layers Node layers
     * @param node_to_layer Reverse mapping of node to layer
     * @param connections Connections
     * @param rng Source of randomness
     */
    Genome(
        NodeId next_node_id, const std::vector<std::pair<unsigned, std::vector<NodeId>>>& layers,
        const std::vector<unsigned>& node_to_layer,
        const std::vector<std::pair<ConnectionHash, Connection>>& connections, Rng& rng
    );

    /**
     * Compute a measure of similarity between two genomes
     *
     * @param other Other genome to measure against
     * @param excess_coeff Coefficient used to compute the part of similarity related to excess genes
     * @param disjoint_coeff Coefficient used to compute the part of similarity related to disjoint genes
     * @param weight_coeff Coefficient used to compute the part of similarity related to genome weight difference
     */
    double similarity(const Genome& other, double excess_coeff, double disjoint_coeff, double weight_coeff) const;

    /**
     * Mutate the genome
     *
     * @param weight_mutation_prob Probability of weight mutation
     * @param add_node_mutation_prob Probability of adding a new node
     * @param add_connection_prob Probability of adding a new connection
     * @param weight_perturbation_prob Probability of modifying the weight of a given connection
     * @param mutation_strength Strength of the weight perturbation
     */
    void mutate(
        double weight_mutation_prob, double add_node_mutation_prob, double add_connection_prob,
        double weight_perturbation_prob, double mutation_strength
    );

    /**
     * Crossover two genomes into a new one
     *
     * @param first First genome to crossover
     * @param first_score Score of the first genome
     * @param second Second genome to crossover
     * @param second_score Score of the second genome
     * @param inherit_connection_disabled_prob Probability of inheriting a given connection in disabled state
     * @param rng Source of randomness
     */
    static Genome crossover(
        const Genome& first, double first_score, const Genome& second, double second_score,
        double inherit_connection_disabled_prob, Rng& rng
    );
};

#endif