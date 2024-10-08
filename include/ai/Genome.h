#ifndef GENOME_HPP
#define GENOME_HPP

#include <cstdint>
#include <optional>
#include <vector>

#include "ai/Connection.h"

using NodeId = std::uint32_t;
using ConnectionHash = std::uint64_t;

class Genome
{
private:
    static ConnectionHash get_connection_hash(NodeId from, NodeId to);
    std::optional<Connection> find_connection(NodeId from, NodeId to);
    void add_connection(NodeId from, NodeId to, double weight);
    void add_node_to_layer(unsigned layer);
public:
    NodeId next_node_id = 0;

    std::vector<std::pair<unsigned, std::vector<NodeId>>> layers;
    std::vector<unsigned> node_to_layer;
    std::vector<std::pair<ConnectionHash, Connection>> connections;

    Genome();
};

#endif