#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <array>
#include <boost/serialization/access.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include "ai/GameStateInput.h"
#include "ai/Genome.h"
#include "ai/NEATConfig.h"

class Network
{
private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & activation_ & nodes_ & in_connections_;
    }

    ActivationFunc activation_;
    std::vector<NodeId> nodes_;
    std::vector<std::vector<std::pair<NodeId, double>>> in_connections_;
public:
    Network(const Genome& genome, const ActivationFunc& activation);
    Network(std::istream& in);
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;
    void save(std::ostream& out) const;
};

#endif