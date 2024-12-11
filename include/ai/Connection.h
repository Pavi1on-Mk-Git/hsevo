#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdint>

using NodeId = std::uint32_t;

struct Connection
{
    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;
    NodeId from, to;
    double weight;
    bool enabled;

    Connection(NodeId from, NodeId to, double weight, bool enabled = true);
};

#endif