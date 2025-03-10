#ifndef EVO_FUNCTIONS_HPP
#define EVO_FUNCTIONS_HPP

#include <ranges>
#include <vector>

#include "logic/Decklist.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

/**
 * Compute scores for the provided populations
 *
 * @tparam Evo Evolutionary algorithm used
 * @tparam Count Population count
 * @param populations Populations to compute scores for
 * @param decklists Decklists used by members of populations
 * @param rng Source of randomness
 * @return Vector of computed scores for each population provided
 */
template <typename Evo, unsigned Count>
std::array<std::vector<unsigned>, Count> score_populations(
    const std::array<std::vector<Evo>, Count>& populations, const std::array<Decklist, Count>& decklists, Rng& rng
)
{
    const unsigned population_size = populations.at(0).size();

    assert(std::ranges::all_of(populations, [&](const auto& population) {
        return population_size == population.size();
    }));

    std::array<std::vector<unsigned>, Count> scores;
    for(auto& score: scores)
        score.resize(population_size, 0);

    std::array<std::vector<std::unique_ptr<PlayerLogic>>, Count> deck_players;
    for(auto [players, decklist, population]: std::views::zip(deck_players, decklists, populations))
    {
        players.reserve(population_size);
        for(const auto& member: population)
            players.push_back(std::make_unique<EvoPlayerLogic<Evo>>(decklist, member, rng));
    }

    auto deck_ids = std::views::iota(0u, Count);
    auto player_ids = std::views::iota(0u, population_size);

    for(auto [fst_deck_id, fst_player_id, snd_deck_id, snd_player_id]:
        std::views::cartesian_product(deck_ids, player_ids, deck_ids, player_ids))
    {
        if(fst_player_id == snd_player_id && fst_deck_id == snd_deck_id)
            continue;

        const auto& fst_player = deck_players.at(fst_deck_id).at(fst_player_id);
        const auto& snd_player = deck_players.at(snd_deck_id).at(snd_player_id);

        auto winner = run_game(fst_player, snd_player, rng);

        switch(winner)
        {
        case GameResult::PLAYER_1:
            scores.at(fst_deck_id).at(fst_player_id)++;
            break;
        case GameResult::PLAYER_2:
            scores.at(snd_deck_id).at(snd_player_id)++;
            break;
        default:
            break;
        }
    }
    return scores;
}

/**
 * Compute score of a contender against the hall of champions
 *
 * @tparam Evolutionary algorithm used
 * @param champions A vector of champions to compare the contender against
 * @param contender Specimen to be compared against the hall of champions
 * @param decklist The decklist used by the contender and all of the champions
 * @param rng Source of randomness
 * @return Score of the contender. If no champions were provided defaults to 1
 */
template <typename Evo>
unsigned score_hall_of_champions(
    const std::vector<Evo>& champions, const Evo& contender, const Decklist& decklist, Rng& rng
)
{
    if(champions.empty())
        return 1;

    std::vector<std::unique_ptr<PlayerLogic>> players;
    players.reserve(champions.size());

    for(const auto& member: champions)
        players.push_back(std::make_unique<EvoPlayerLogic<Evo>>(decklist, member, rng));

    std::unique_ptr<PlayerLogic> contender_player = std::make_unique<EvoPlayerLogic<Evo>>(decklist, contender, rng);

    return std::ranges::fold_left(players, 0, [&](unsigned total, const auto& player) {
        return total + (run_game(contender_player, player, rng) == GameResult::PLAYER_1 ? 1 : 0);
    });
}

#endif