#include "ai/EvoSpecimen.hpp"

#include <algorithm>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cmath>
#include <ranges>

static const double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;

void EvoSpecimen::mutate()
{
    double random_evo_coeff_a = rng_.get().normal(), random_evo_coeff_b = rng_.get().normal();

    std::ranges::transform(mutation_strengths_, mutation_strengths_.begin(), [&](double strength) {
        return std::max(
            strength * std::exp(
                           random_evo_coeff_a / std::sqrt(2. * std::sqrt(GameStateInput::INPUT_SIZE)) +
                           random_evo_coeff_b / std::sqrt(2. * GameStateInput::INPUT_SIZE)
                       ),
            1e-5
        );
    });

    std::ranges::transform(weights_, mutation_strengths_, weights_.begin(), [&](double weight, double strength) {
        return std::clamp(weight + rng_.get().normal(0., strength), MIN_WEIGHT, MAX_WEIGHT);
    });
}

EvoSpecimen::EvoSpecimen(double init_mutation_strength, Rng& rng): rng_(rng)
{
    std::ranges::generate(weights_, [&]() { return rng.uniform_real(MIN_WEIGHT, MAX_WEIGHT); });
    std::ranges::fill(mutation_strengths_, init_mutation_strength);
}

EvoSpecimen::EvoSpecimen(std::istream& in, Rng& rng): rng_(rng)
{
    boost::archive::text_iarchive archive(in);
    archive >> *this;
}

double EvoSpecimen::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    double score = 0.;
    for(auto [weight, input]: std::views::zip(weights_, input_vec))
        score += weight * input;
    return score;
}

void EvoSpecimen::save(std::ostream& out) const
{
    boost::archive::text_oarchive archive(out);
    archive << *this;
}
