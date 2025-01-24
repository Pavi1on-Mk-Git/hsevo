#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ai/GameStateInput.h"
#include "ai/Genome.h"
#include "ai/Network.hpp"

auto get_test_genome()
{
    NodeId next_node_id = 54;
    std::vector<std::pair<unsigned, std::vector<NodeId>>> layers;

    auto& first_layer = layers.emplace_back(0, std::vector<NodeId>{});
    for(NodeId i = 0; i <= GameStateInput::INPUT_SIZE; ++i)
        first_layer.second.push_back(i);

    layers.emplace_back(std::numeric_limits<unsigned>::max() / 2, std::vector<NodeId>{GameStateInput::INPUT_SIZE + 2});

    layers.emplace_back(std::numeric_limits<unsigned>::max(), std::vector<NodeId>{GameStateInput::INPUT_SIZE + 1});

    std::vector<unsigned> node_to_layer;

    for(NodeId i = 0; i <= GameStateInput::INPUT_SIZE; ++i)
        node_to_layer.push_back(0);

    node_to_layer.push_back(std::numeric_limits<unsigned>::max());
    node_to_layer.push_back(std::numeric_limits<unsigned>::max() / 2);

    std::vector<std::pair<ConnectionHash, Connection>> connections;

    for(NodeId i = 0; i <= GameStateInput::INPUT_SIZE; ++i)
    {
        ConnectionHash hash = 0;
        hash |= static_cast<ConnectionHash>(i);
        hash |= static_cast<ConnectionHash>(GameStateInput::INPUT_SIZE + 1) << std::numeric_limits<NodeId>::digits;
        connections.emplace_back(hash, Connection(i, GameStateInput::INPUT_SIZE + 1, 0.5));
    }

    ConnectionHash hash = 0;
    hash |= static_cast<ConnectionHash>(0);
    hash |= static_cast<ConnectionHash>(GameStateInput::INPUT_SIZE + 2) << std::numeric_limits<NodeId>::digits;

    connections.emplace_back(hash, Connection(0, GameStateInput::INPUT_SIZE + 2, 0.1));

    hash = 0;
    hash |= static_cast<ConnectionHash>(1);
    hash |= static_cast<ConnectionHash>(GameStateInput::INPUT_SIZE + 2) << std::numeric_limits<NodeId>::digits;

    connections.emplace_back(hash, Connection(1, GameStateInput::INPUT_SIZE + 2, 0.1));

    hash = 0;
    hash |= static_cast<ConnectionHash>(GameStateInput::INPUT_SIZE + 2);
    hash |= static_cast<ConnectionHash>(GameStateInput::INPUT_SIZE + 1) << std::numeric_limits<NodeId>::digits;

    connections.emplace_back(hash, Connection(GameStateInput::INPUT_SIZE + 2, GameStateInput::INPUT_SIZE + 1, 0.3));

    Rng rng(42);

    return Genome(next_node_id, layers, node_to_layer, connections, rng);
}

TEST_CASE("Network forward pass")
{
    auto test_genome = get_test_genome();

    Network test_network(test_genome, ActivationFuncType::ID);

    std::array<double, GameStateInput::INPUT_SIZE> input;
    std::ranges::fill(input, 1.);

    double score = test_network.score_vec(input);

    REQUIRE_THAT(score, Catch::Matchers::WithinAbs(26.06, 0.000001));
}

TEST_CASE("Genome similarity")
{
    NodeId next_node_id = 5;
    std::vector<std::pair<unsigned, std::vector<NodeId>>> layers{
        {0, {0, 1, 2, 3}},
        {std::numeric_limits<unsigned>::max(), {4}},
    };
    std::vector<unsigned> node_to_layer{0, 0, 0, 0, std::numeric_limits<unsigned>::max()};

    std::vector<std::pair<ConnectionHash, Connection>> fst_connections;
    for(auto [from, weight]: std::views::zip(std::vector<NodeId>{0, 3, 2}, std::vector<double>{0.7, 0.4, 0.5}))
    {
        ConnectionHash hash = 0;
        hash |= static_cast<ConnectionHash>(from);
        hash |= static_cast<ConnectionHash>(4) << std::numeric_limits<NodeId>::digits;
        fst_connections.emplace_back(hash, Connection(from, 4, weight));
    }

    std::vector<std::pair<ConnectionHash, Connection>> snd_connections;
    for(auto [from, weight]: std::views::zip(std::vector<NodeId>{0, 1, 3}, std::vector<double>{0.2, 0.85, 0.11}))
    {
        ConnectionHash hash = 0;
        hash |= static_cast<ConnectionHash>(from);
        hash |= static_cast<ConnectionHash>(4) << std::numeric_limits<NodeId>::digits;
        snd_connections.emplace_back(hash, Connection(from, 4, weight));
    }

    Rng rng(42);

    Genome fst(next_node_id, layers, node_to_layer, fst_connections, rng);
    Genome snd(next_node_id, layers, node_to_layer, snd_connections, rng);

    double similarity = fst.similarity(snd, 1., 1., 0.4);

    REQUIRE_THAT(similarity, Catch::Matchers::WithinAbs(0.8246666, 0.000001));
}
