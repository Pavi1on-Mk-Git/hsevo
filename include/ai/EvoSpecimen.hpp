#ifndef EVO_SPECIMEN_HPP
#define EVO_SPECIMEN_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>

#include "ai/GameStateInput.h"
#include "utils/Rng.h"

/**
 * Evolutionary algorithm specimen
 */
class EvoSpecimen
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
        archive & weights_ & mutation_strengths_;
    }

    /**
     * Algorithm weights
     */
    std::array<double, GameStateInput::INPUT_SIZE> weights_;

    /**
     * Algorithm mutation strengths
     */
    std::array<double, GameStateInput::INPUT_SIZE> mutation_strengths_;

    /**
     * Source of randomness
     */
    std::reference_wrapper<Rng> rng_;
public:
    /**
     * Construct a specimen
     * @param init_mutation_strength Initial mutation strength
     * @param rng Source of randomness
     */
    EvoSpecimen(double init_mutation_strength, Rng& rng);

    /**
     * Construct a specimen from a stream
     * @param in Stream to load the specimen from
     * @param rng Source of randomness
     */
    EvoSpecimen(std::istream& in, Rng& rng);

    /**
     * Mutate the specimen
     */
    void mutate();

    /**
     * Compute the specimen score
     *
     * @param input_vec Specimen input
     * @return Computed score
     */
    double score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const;

    /**
     * Save the speciment to a stream
     *
     * @param out Stream to save the specimen to
     */
    void save(std::ostream& out) const;
};

#endif
