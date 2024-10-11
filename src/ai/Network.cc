#include "ai/Network.h"

#include <algorithm>
#include <numeric>

Network::Network(const Genome& genome, ActivationFunc activation): activation(activation)
{
    nodes_.reserve(genome.next_node_id);

    for(auto [layer_id, layer_nodes]: genome.layers)
        for(NodeId node: layer_nodes)
            nodes_.push_back(node);

    in_connections_.resize(genome.next_node_id);

    for(auto [connection_hash, connection]: genome.connections)
        if(connection.enabled)
            in_connections_.at(connection.to).emplace_back(connection.from, connection.weight);
}

double Network::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    std::vector<double> node_values;
    node_values.resize(nodes_.size());

    node_values.at(0) = 1;

    for(unsigned node_id = 1; node_id <= GameStateInput::INPUT_SIZE; ++node_id)
        node_values.at(node_id) = input_vec.at(node_id - 1);

    for(unsigned node_id = GameStateInput::INPUT_SIZE + 1; node_id < nodes_.size(); ++node_id)
        node_values.at(node_id) = activation(std::accumulate(
            in_connections_.at(node_id).begin(), in_connections_.at(node_id).end(), 0.,
            [&node_values](double init, const auto& connection) {
                return init + node_values.at(connection.first) * connection.second;
            }
        ));

    return node_values.at(nodes_.size() - 1);
}