#ifndef EVO_SCORER_HPP
#define EVO_SCORER_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>

#include "ai/EvoSpecimen.h"
#include "ai/GameStateInput.h"
#include "utils/Rng.h"

/**
 * Evolutionary algorithm score computation class
 */
class EvoScorer
{
private:
    friend class boost::serialization::access;

    /**
     * Serialize the algorithm data into a boost archive
     * @param archive Archive to serialize the data into
     * @param version Unused
     */
    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & weights_;
    }

    /**
     * Algorithm weights
     */
    std::array<double, GameStateInput::INPUT_SIZE> weights_;
public:
    /**
     * Construct a Scorer
     * @param specimen Source evolutionary algorithm specimen
     */
    EvoScorer(const EvoSpecimen& specimen);

    /**
     * Construct a Scorer from a stream
     * @param in Stream to load the Scorer from
     */
    EvoScorer(std::istream& in);


    /**
     * Compute the Scorer score
     *
     * @param input_vec Scorer input
     * @return Computed score
     */
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;

    /**
     * Save the Scorert to a stream
     *
     * @param out Stream to save the Scorer to
     */
    void save(std::ostream& out) const;
};

#endif
