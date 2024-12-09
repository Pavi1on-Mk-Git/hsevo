#include "ai/SimpleEvo.hpp"

#include <algorithm>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cmath>
#include <ranges>

static const double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;

void SimpleEvo::mutate()
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

auto SimpleEvo::init_population(unsigned population_size, double init_mutation_strength, Rng& rng)
{
    std::vector<SimpleEvo> population;
    population.reserve(population_size);
    std::generate_n(std::back_inserter(population), population_size, [&]() {
        return SimpleEvo(init_mutation_strength, rng);
    });
    return population;
}

auto SimpleEvo::mutate_population(
    const std::vector<SimpleEvo>& population, unsigned mutants_size, ScoringFunc scoring_func, Rng& rng
)
{
    std::vector<SimpleEvo> mutants;
    mutants.reserve(mutants_size + population.size());

    for(unsigned mutant_id = 0; mutant_id < mutants_size; ++mutant_id)
    {
        const unsigned to_mutate = rng.uniform_int(0, population.size() - 1);
        auto mutant = population.at(to_mutate);
        mutant.mutate();
        mutants.push_back(mutant);
    }

    std::ranges::move(population, std::back_inserter(mutants));

    auto scores = scoring_func(mutants);

    std::vector<std::pair<SimpleEvo, unsigned>> mutants_with_scores;
    mutants_with_scores.reserve(mutants.size());

    std::ranges::transform(
        mutants, scores, std::back_inserter(mutants_with_scores),
        [](const auto& member, unsigned score) { return std::make_pair(member, score); }
    );

    return mutants_with_scores;
}

SimpleEvo::SimpleEvo(double init_mutation_strength, Rng& rng): rng_(rng)
{
    std::ranges::generate(weights_, [&]() { return rng.uniform_real(MIN_WEIGHT, MAX_WEIGHT); });
    std::ranges::fill(mutation_strengths_, init_mutation_strength);
}

SimpleEvo::SimpleEvo(std::istream& in, Rng& rng): rng_(rng)
{
    boost::archive::text_iarchive archive(in);
    archive >> *this;
}

double SimpleEvo::score_vec(const std::array<double, GameStateInput::INPUT_SIZE>& input_vec) const
{
    double score = 0.;
    for(auto [weight, input]: std::views::zip(weights_, input_vec))
        score += weight * input;
    return score;
}

std::pair<SimpleEvo, unsigned> SimpleEvo::evolve(
    unsigned mu, unsigned lambda, double init_mutation_strength, ScoringFunc scoring_func, unsigned iterations, Rng& rng
)
{
    auto population = init_population(mu, init_mutation_strength, rng);

    auto best_member = std::make_pair(SimpleEvo(init_mutation_strength, rng), 0);

    for(unsigned iteration = 0; iteration < iterations; ++iteration)
    {
        auto mutants_with_scores = mutate_population(population, lambda, scoring_func, rng);
        std::ranges::nth_element(
            mutants_with_scores.begin(), mutants_with_scores.begin() + mu, mutants_with_scores.end(),
            [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
        );

        std::ranges::transform(
            mutants_with_scores.begin(), mutants_with_scores.begin() + mu, population.begin(),
            [](const auto& member_with_score) { return member_with_score.first; }
        );

        best_member = *std::ranges::max_element(
            mutants_with_scores.begin(), mutants_with_scores.begin() + mu,
            [](const auto& fst, const auto& snd) { return fst.second < snd.second; }
        );
    }

    return best_member;
}

void SimpleEvo::save(std::ostream& out) const
{
    boost::archive::text_oarchive archive(out);
    archive << *this;
}
