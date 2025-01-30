#define DRAW_NETWORK

#include <algorithm>
#include <boost/archive/archive_exception.hpp>
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

#include "ai/Network.hpp"

void draw_network(const Network& network, unsigned node_radius, unsigned layer_spacing)
{
    raylib::Window window(1600, 1000, "Network visualization");

    while(!window.ShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        std::vector<unsigned> node_layers;
        node_layers.resize(network.in_connections_.size(), 0);

        for(auto [layer, connections]: std::views::zip(node_layers, network.in_connections_))
        {
            for(const auto& connection: connections)
                layer = std::max(layer, node_layers.at(connection.first) + 1);
        }

        std::vector<unsigned> nodes_in_layer;
        nodes_in_layer.resize(std::ranges::max(node_layers) + 1, 0);

        for(const auto& layer: node_layers)
            ++nodes_in_layer.at(layer);

        node_layers.erase(node_layers.begin());

        const unsigned width = 1600;
        const unsigned height = 1000;
        const unsigned x_spacing = 10;

        std::vector<unsigned> current_node_x_positions;
        std::ranges::transform(nodes_in_layer, std::back_inserter(current_node_x_positions), [&](const auto& count) {
            return (width - (2 * count * node_radius + (count - 1) * x_spacing)) / 2 + node_radius;
        });

        const unsigned y_margin = (height - (2 * nodes_in_layer.size() * node_radius +
                                             (nodes_in_layer.size() - 1) * layer_spacing)) /
                                      2 +
                                  node_radius;

        std::vector<raylib::Vector2> node_positions;
        std::ranges::transform(node_layers, std::back_inserter(node_positions), [&](const auto& layer) {
            auto& current_position = current_node_x_positions.at(layer);
            unsigned x = current_position;
            current_position += 2 * node_radius + x_spacing;
            return raylib::Vector2(x, y_margin + (2 * node_radius + layer_spacing) * layer);
        });

        for(auto [to, connections]: std::views::zip(node_positions, network.in_connections_ | std::views::drop(1)))
        {
            for(const auto& connection: connections)
            {
                const auto& start = node_positions.at(connection.first);
                raylib::Color colour(255, 0, 0, 25 + 230 * (connection.second / 10.));
                DrawLineEx(start, to, 2.f, colour);
            }
        }

        for(const auto& position: node_positions | std::views::take(GameStateInput::INPUT_SIZE))
            DrawCircleV(position, node_radius, BLUE);
        for(const auto& position: node_positions | std::views::drop(GameStateInput::INPUT_SIZE))
            DrawCircleV(position, node_radius, ORANGE);
        DrawCircleV(*(node_positions.end() - 1), node_radius, GREEN);

        EndDrawing();
    }
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "This program takes one argument: name of the file from which to load the network." << std::endl;
        return 1;
    }

    try
    {
        std::ifstream in(argv[1]);
        Network net(in);
        draw_network(net, 10, 200);
    }
    catch(boost::archive::archive_exception& e)
    {
        std::cerr << "Can't load the network from provided file. Please make sure the provide path contains a valid "
                     "network"
                  << std::endl;
        return 2;
    }

    return 0;
}
