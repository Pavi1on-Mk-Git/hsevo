#ifndef EVO_FUNCTIONS_HPP
#define EVO_FUNCTIONS_HPP

#include <ranges>
#include <vector>

#include "logic/Decklist.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"

template <typename Evo, unsigned Count>
std::array<std::vector<unsigned>, Count> score_populations(
    const std::array<std::vector<Evo>, Count>& populations, const std::array<Decklist, Count>& decklists
)
{
    const unsigned population_size = populations.at(0).size();

    assert(std::ranges::all_of(populations, [&populations](const auto& population) {
        return populations.at(0).size() == population.size();
    }));

    std::array<std::vector<unsigned>, Count> scores;
    for(auto& score: scores)
        score.resize(population_size, 0);

    std::array<std::vector<std::unique_ptr<PlayerLogic>>, Count> deck_players;
    for(auto [players, decklist, population]: std::views::zip(deck_players, decklists, populations))
    {
        players.reserve(population_size);
        for(const auto& member: population)
            players.push_back(std::make_unique<EvoPlayerLogic<Evo>>(decklist, member));
    }

    auto deck_ids = std::views::iota(0u, Count);
    auto player_ids = std::views::iota(0u, population_size);

    for(auto [fst_deck_id, fst_player_id, snd_deck_id, snd_player_id]:
        std::views::cartesian_product(deck_ids, player_ids, deck_ids, player_ids))
    {
        const auto& fst_player = deck_players.at(fst_deck_id).at(fst_player_id);
        const auto& snd_player = deck_players.at(snd_deck_id).at(snd_player_id);

        auto winner = run_game(fst_player, snd_player);

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

#endif