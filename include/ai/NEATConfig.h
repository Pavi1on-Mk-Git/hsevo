#ifndef NEAT_CONFIG_H
#define NEAT_CONFIG_H

#include <functional>

struct Network;

using ScoringFunc = std::function<std::vector<unsigned>(std::vector<Network>)>;
using ActivationFunc = std::function<double(double)>;

struct NEATConfig
{
    unsigned population_size;
    unsigned iterations;
    ScoringFunc scoring_func;
    ActivationFunc activation;
};

#endif