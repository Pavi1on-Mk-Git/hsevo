#include "ai/Genome.h"

#include <algorithm>
#include <limits>

#include "ai/GameStateInput.h"

ConnectionHash Genome::get_connection_hash(NodeId from, NodeId to)
{
    ConnectionHash hash = 0;
    hash |= static_cast<ConnectionHash>(from);
    hash |= static_cast<ConnectionHash>(to) << std::numeric_limits<NodeId>::digits;
    return hash;
}

Connection* Genome::find_connection(NodeId from, NodeId to)
{
    const ConnectionHash hash = get_connection_hash(from, to);

    auto found_connection = std::ranges::find_if(connections, [&hash](const auto& entry) {
        return entry.first == hash;
    });

    return found_connection != connections.end() ? &found_connection->second : nullptr;
}

void Genome::add_connection(NodeId from, NodeId to, double weight)
{
    connections.emplace_back(get_connection_hash(from, to), Connection(from, to, weight));
}

void Genome::add_node_to_layer(unsigned layer)
{
    auto found_layer = std::ranges::lower_bound(layers, layer, {}, [](const auto& entry) { return entry.first; });

    if(found_layer != layers.end() && found_layer->first == layer)
    {
        if((std::ranges::find(found_layer->second, next_node_id) != found_layer->second.end()))
            return;

        found_layer->second.push_back(next_node_id++);
    }
    else
    {
        auto& new_layer = layers.emplace_back(layer, std::vector<NodeId>{});
        new_layer.second.push_back(next_node_id++);

        auto bound = std::ranges::lower_bound(layers, new_layer.first, {}, [](const auto& layer) {
            return layer.first;
        });

        std::ranges::rotate(bound, layers.end() - 1, layers.end());
    }

    node_to_layer_.push_back(layer);
}

void Genome::mutate_weight(Connection& connection, double weight_perturbation_prob, double mutation_strength)
{
    connection.weight = rng_.get().uniform_real() < weight_perturbation_prob ?
                            std::clamp(
                                connection.weight + rng_.get().normal(0., mutation_strength), Connection::MIN_WEIGHT,
                                Connection::MAX_WEIGHT
                            ) :
                            rng_.get().uniform_real(Connection::MIN_WEIGHT, Connection::MAX_WEIGHT);
}

void Genome::mutate_add_node()
{
    unsigned connection_id;

    do
    {
        connection_id = rng_.get().uniform_int(0, connections.size() - 1);
    }
    while(!connections.at(connection_id).second.enabled);

    Connection& connection = connections.at(connection_id).second;

    connection.enabled = false;
    const unsigned from = connection.from, to = connection.to;
    const double weight = connection.weight;

    add_connection(from, next_node_id, 1.);
    add_connection(next_node_id, to, weight);

    add_connection(0, next_node_id, 0.);

    add_node_to_layer(node_to_layer_.at(from) / 2 + node_to_layer_.at(to) / 2);
}

void Genome::mutate_add_connection()
{
    unsigned layer_from, layer_to;

    do
    {
        layer_from = rng_.get().uniform_int(0, layers.size() - 1);
        layer_to = rng_.get().uniform_int(0, layers.size() - 1);
    }
    while(layer_from == layer_to);

    if(layer_to < layer_from)
        std::swap(layer_to, layer_from);

    const auto& layer_from_nodes = layers.at(layer_from).second;
    const auto& layer_to_nodes = layers.at(layer_to).second;

    NodeId node_from = layer_from_nodes.at(rng_.get().uniform_int(0, layer_from_nodes.size() - 1)),
           node_to = layer_to_nodes.at(rng_.get().uniform_int(0, layer_to_nodes.size() - 1));

    auto* connection = find_connection(node_from, node_to);
    if(connection)
        connection->enabled = true;
    else
        add_connection(node_from, node_to, rng_.get().uniform_real(Connection::MIN_WEIGHT, Connection::MAX_WEIGHT));
}

Genome::Genome(Rng& rng): rng_(rng), next_node_id(0)
{
    node_to_layer_.reserve(GameStateInput::INPUT_SIZE + 1);

    for(NodeId node_id = 0; node_id <= GameStateInput::INPUT_SIZE; ++node_id)
        add_node_to_layer(0);

    add_node_to_layer(std::numeric_limits<unsigned>::max());

    connections.reserve(GameStateInput::INPUT_SIZE);
    for(unsigned from = 0; from <= GameStateInput::INPUT_SIZE; ++from)
        add_connection(
            from, GameStateInput::INPUT_SIZE + 1,
            rng_.get().uniform_real(Connection::MIN_WEIGHT, Connection::MAX_WEIGHT)
        );
}

Genome::Genome(
    NodeId next_node_id, const std::vector<std::pair<unsigned, std::vector<NodeId>>>& layers,
    const std::vector<unsigned>& node_to_layer, const std::vector<std::pair<ConnectionHash, Connection>>& connections,
    Rng& rng
): rng_(rng), node_to_layer_(node_to_layer), next_node_id(next_node_id), layers(layers), connections(connections)
{}

double Genome::similarity(const Genome& other, double excess_coeff, double disjoint_coeff, double weight_coeff) const
{
    unsigned excess_count = 0, disjoint_count = 0, matching_count = 0;
    double weight_diff = 0.;

    unsigned this_id = 0, other_id = 0;
    while(this_id != connections.size() || other_id != other.connections.size())
    {
        if(this_id == connections.size())
        {
            ++excess_count;
            ++other_id;
        }
        else if(other_id == other.connections.size())
        {
            ++excess_count;
            ++this_id;
        }
        else
        {
            const auto& this_connection = connections.at(this_id);
            const auto& other_connection = other.connections.at(other_id);

            if(this_connection.first == other_connection.first)
            {
                ++matching_count;
                weight_diff += std::abs(this_connection.second.weight - other_connection.second.weight);
                ++this_id;
                ++other_id;
            }
            else
            {
                ++disjoint_count;
                if(this_connection.first < other_connection.first)
                    ++this_id;
                else
                    ++other_id;
            }
        }
    }

    weight_diff = matching_count ? weight_diff / matching_count : 0.;

    const unsigned longer_genome_length = std::max(connections.size(), other.connections.size());

    return (excess_coeff * excess_count + disjoint_coeff * disjoint_count) / longer_genome_length +
           weight_coeff * weight_diff;
}

void Genome::mutate(
    double weight_mutation_prob, double add_node_mutation_prob, double add_connection_prob,
    double weight_perturbation_prob, double mutation_strength
)
{
    for(auto& [hash, connection]: connections)
        if(rng_.get().uniform_real() < weight_mutation_prob)
            mutate_weight(connection, weight_perturbation_prob, mutation_strength);

    if(rng_.get().uniform_real() < add_node_mutation_prob)
        mutate_add_node();

    if(rng_.get().uniform_real() < add_connection_prob)
        mutate_add_connection();
}

Genome Genome::crossover(
    const Genome& first, double first_score, const Genome& second, double second_score,
    double inherit_connection_disabled_prob, Rng& rng
)
{
    const bool is_first_stronger = first_score > second_score;

    const Genome& stronger = is_first_stronger ? first : second;
    const Genome& weaker = is_first_stronger ? second : first;

    std::vector<std::pair<ConnectionHash, Connection>> new_connections;
    new_connections.reserve(stronger.connections.size());

    for(const auto& stronger_connection: stronger.connections)
    {
        auto matching_connection = std::ranges::find_if(
            weaker.connections, [&stronger_connection](const auto& weaker_connection
                                ) { return weaker_connection.first == stronger_connection.first; }
        );

        if(matching_connection == weaker.connections.end())
            new_connections.push_back(stronger_connection);
        else
        {
            const unsigned toss_up_result = rng.uniform_int(0, 1);
            auto to_add = toss_up_result == 0 ? stronger_connection : *matching_connection;

            if(!stronger_connection.second.enabled && !matching_connection->second.enabled &&
               rng.uniform_real() >= inherit_connection_disabled_prob)
                to_add.second.enabled = true;

            new_connections.push_back(to_add);
        }
    }

    return Genome(stronger.next_node_id, stronger.layers, stronger.node_to_layer_, new_connections, rng);
}
