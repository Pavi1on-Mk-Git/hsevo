#ifndef EVO_FUNCTIONS_HPP
#define EVO_FUNCTIONS_HPP

#include <ranges>
#include <vector>

#include "logic/Decklist.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"

template <typename Evo>
std::vector<std::vector<unsigned>> score_populations(
    const std::vector<std::vector<Evo>>& populations, const std::vector<Decklist>& decklists
)
{
    assert(!populations.empty());

    const unsigned population_count = populations.size();
    const unsigned population_size = populations.at(0).size();

    assert(populations.size() == decklists.size());
    assert(std::ranges::all_of(populations, [&populations](const auto& population) {
        return populations.at(0).size() == population.size();
    }));

    std::vector<std::vector<unsigned>> scores(population_count);
    for(auto& score: scores)
        score.resize(population_size, 0);

    std::vector<std::vector<std::unique_ptr<PlayerLogic>>> deck_players(population_count);
    for(auto [players, decklist, population]: std::views::zip(deck_players, decklists, populations))
    {
        players.reserve(population_size);
        for(const auto& member: population)
            players.push_back(std::make_unique<EvoPlayerLogic<Evo>>(decklist, member));
    }

    auto deck_ids = std::views::iota(0u, population_count);
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