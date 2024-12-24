#include "ai/EvoSpecimen.h"

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

    std::ranges::transform(weights, mutation_strengths_, weights.begin(), [&](double weight, double strength) {
        return std::clamp(weight + rng_.get().normal(0., strength), MIN_WEIGHT, MAX_WEIGHT);
    });
}

EvoSpecimen::EvoSpecimen(double init_mutation_strength, Rng& rng): rng_(rng)
{
    std::ranges::generate(weights, [&]() { return rng.uniform_real(MIN_WEIGHT, MAX_WEIGHT); });
    std::ranges::fill(mutation_strengths_, init_mutation_strength);
}
