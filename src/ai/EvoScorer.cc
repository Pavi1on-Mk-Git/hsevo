#include "ai/EvoScorer.hpp"

#include <algorithm>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cmath>
#include <ranges>

EvoScorer::EvoScorer(const EvoSpecimen& specimen): weights_(specimen.weights) {}

EvoScorer::EvoScorer(std::istream& in)
{
    boost::archive::text_iarchive archive(in);
    archive >> *this;
}

double EvoScorer::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    double score = 0.;
    for(auto [weight, input]: std::views::zip(weights_, input_vec))
        score += weight * input;
    return score;
}

void EvoScorer::save(std::ostream& out) const
{
    boost::archive::text_oarchive archive(out);
    archive << *this;
}
