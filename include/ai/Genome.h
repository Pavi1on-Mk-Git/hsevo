#ifndef GENOME_HPP
#define GENOME_HPP

#include <cstdint>
#include <optional>
#include <vector>

#include "ai/Connection.h"
#include "utils/Rng.h"

using NodeId = std::uint32_t;
using ConnectionHash = std::uint64_t;

class Genome
{
private:
    std::reference_wrapper<Rng> rng_;

    static ConnectionHash get_connection_hash(NodeId from, NodeId to);
    std::optional<Connection> find_connection(NodeId from, NodeId to);
    void add_connection(NodeId from, NodeId to, double weight);
    void add_node_to_layer(unsigned layer);
    void mutate_weight(Connection& connection, double weight_perturbation_prob, double mutation_strength);
    void mutate_add_node();
    void mutate_add_connection();
public:
    NodeId next_node_id = 0;

    std::vector<std::pair<unsigned, std::vector<NodeId>>> layers;
    std::vector<unsigned> node_to_layer;
    std::vector<std::pair<ConnectionHash, Connection>> connections;

    Genome(Rng& rng);
    Genome(
        NodeId next_node_id, const std::vector<std::pair<unsigned, std::vector<NodeId>>>& layers,
        const std::vector<unsigned>& node_to_layer,
        const std::vector<std::pair<ConnectionHash, Connection>>& connections, Rng& rng
    );
    double similarity(const Genome& other, double excess_coeff, double disjoint_coeff, double weight_coeff) const;
    void mutate(
        double weight_mutation_prob, double add_node_mutation_prob, double add_connection_prob,
        double weight_perturbation_prob, double mutation_strength
    );
    static Genome crossover(
        const Genome& first, double first_score, const Genome& second, double second_score,
        double inherit_connection_disabled_prob, Rng& rng
    );
};

#endif