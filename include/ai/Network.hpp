#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <array>
#include <boost/serialization/access.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include "ai/GameStateInput.h"
#include "ai/Genome.h"
#include "ai/NEATConfig.h"

/**
 * Neural network
 */
class Network
{
private:
    friend class boost::serialization::access;

    /**
     * Serialize the network into a boost archive
     * @param archive Archive to serialize the network into
     * @param version Unused
     */
    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & activation_ & nodes_ & in_connections_;
    }

    /**
     * Activation function used by the network
     */
    ActivationFunc activation_;

    /**
     * Nodes present in the network
     */
    std::vector<NodeId> nodes_;

    /**
     * Input connections for each node present in the network
     */
    std::vector<std::vector<std::pair<NodeId, double>>> in_connections_;
public:
    /**
     * Construct a network from a genome and an activation function
     * @param genome Source genome
     * @param activation Source activation function
     */
    Network(const Genome& genome, const ActivationFunc& activation);

    /**
     * Construct a network from a stream
     * @param in Stream to load the network from
     */
    Network(std::istream& in);

    /**
     * Compute the network score
     *
     * @param input_vec Network input
     * @return Computed score
     */
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;

    /**
     * Save the network to a stream
     * @param out Stream to save the network to
     */
    void save(std::ostream& out) const;
};

#endif