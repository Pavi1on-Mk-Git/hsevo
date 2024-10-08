#ifndef NETWORK_H
#define NETWORK_H

#include <array>

#include "ai/GameStateInput.h"
#include "ai/Genome.h"
#include "ai/NEATConfig.h"

class Network
{
private:
    ActivationFunc activation;
    std::vector<NodeId> nodes_;
    std::vector<std::vector<std::pair<NodeId, double>>> in_connections_;
public:
    Network(const Genome& genome, ActivationFunc activation);
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;
};
#endif