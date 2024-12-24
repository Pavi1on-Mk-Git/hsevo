#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdint>

using NodeId = std::uint32_t;

/**
 * Connection between two nodes with a given weight. It can be enabled or not
 */
struct Connection
{
    /**
     * Weight bounds of an connection
     */
    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;

    /**
     * Ids of connection's source and target nodes
     */
    NodeId from, to;

    /**
     * Connection weight
     */
    double weight;

    /**
     * Connection status
     */
    bool enabled;

    /**
     * Construct a Connection between two nodes
     *
     * @param from Id of the source node
     * @param to Id of the target node
     * @param weight Weight of the connection
     * @param enabled Connection status. Defaults to enabled
     */
    Connection(NodeId from, NodeId to, double weight, bool enabled = true);
};

#endif