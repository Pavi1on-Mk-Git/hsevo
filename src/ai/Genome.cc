#include "ai/Genome.h"

#include "ai/GameStateInput.h"
#include "utils/Rng.h"

ConnectionHash Genome::get_connection_hash(NodeId from, NodeId to)
{
    ConnectionHash hash = 0;
    hash |= static_cast<ConnectionHash>(from);
    hash |= static_cast<ConnectionHash>(to) << sizeof(NodeId);
    return hash;
}

std::optional<Connection> Genome::find_connection(NodeId from, NodeId to)
{
    const ConnectionHash hash = get_connection_hash(from, to);

    auto found_connection = std::find_if(connections.begin(), connections.end(), [&hash](const auto& entry) {
        return entry.first == hash;
    });

    if(found_connection != connections.end())
        return found_connection->second;
    return std::nullopt;
}

void Genome::add_connection(NodeId from, NodeId to, double weight)
{
    connections.emplace_back(get_connection_hash(from, to), Connection{from, to, weight, true});
}

void Genome::add_node_to_layer(unsigned layer)
{
    auto found_layer = std::find_if(layers.begin(), layers.end(), [&layer](const auto& entry) {
        return entry.first == layer;
    });

    if(found_layer != layers.end())
    {
        if((std::find(found_layer->second.begin(), found_layer->second.end(), next_node_id) != found_layer->second.end()
           ))
            return;

        found_layer->second.push_back(next_node_id++);
    }
    else
        layers.emplace_back(layer, std::vector<NodeId>{}).second.push_back(next_node_id++);

    node_to_layer.push_back(layer);
}

Genome::Genome()
{
    connections.reserve(GameStateInput::INPUT_SIZE);
    for(unsigned from = 0; from < GameStateInput::INPUT_SIZE; ++from)
        add_connection(from, GameStateInput::INPUT_SIZE, Rng::instance()->uniform_real());

    node_to_layer.reserve(GameStateInput::INPUT_SIZE + 1);

    for(NodeId node_id = 0; node_id < GameStateInput::INPUT_SIZE; ++node_id)
        add_node_to_layer(0);

    add_node_to_layer(std::numeric_limits<unsigned>::max());
}