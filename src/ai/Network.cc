#include "ai/Network.hpp"

#include <algorithm>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <ranges>

Network::Network(const Genome& genome, const ActivationFunc& activation): activation_(activation)
{
    nodes_.reserve(genome.next_node_id);

    for(const auto& [layer_id, layer_nodes]: genome.layers)
        for(NodeId node: layer_nodes)
            nodes_.push_back(node);

    in_connections_.resize(genome.next_node_id);

    for(const auto& [connection_hash, connection]: genome.connections)
        if(connection.enabled)
            in_connections_.at(connection.to).emplace_back(connection.from, connection.weight);
}

Network::Network(std::istream& in)
{
    boost::archive::text_iarchive archive(in);
    archive >> *this;
}

double Network::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    std::vector<double> node_values;
    node_values.resize(nodes_.size());

    node_values.at(0) = 1;

    std::ranges::copy(input_vec, node_values.begin() + 1);

    for(auto [node_value, in_connections]:
        std::views::zip(node_values, in_connections_) | std::views::drop(GameStateInput::INPUT_SIZE + 1))
        node_value = activation_(std::ranges::fold_left(
            in_connections, 0.,
            [&node_values](double init, const auto& connection) {
                return init + node_values.at(connection.first) * connection.second;
            }
        ));

    return node_values.at(nodes_.size() - 1);
}

void Network::save(std::ostream& out) const
{
    boost::archive::text_oarchive archive(out);
    archive << *this;
}
