#ifndef EVO_FUNCTIONS_HPP
#define EVO_FUNCTIONS_HPP

#include <ranges>
#include <vector>

#include "logic/Decklist.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"

template <typename Evo>
std::vector<unsigned> score_member(const std::vector<Evo>& population, const Decklist& decklist)
{
    std::vector<unsigned> scores(population.size(), 0);

    std::vector<std::unique_ptr<PlayerLogic>> players;
    players.reserve(population.size());


    for(const auto& member: population)
        players.push_back(std::make_unique<EvoPlayerLogic<Evo>>(decklist, member));

    auto players_n_scores = std::views::zip(players, scores);

    for(auto [first_player, first_player_score, second_player, second_player_score]:
        std::views::cartesian_product(players_n_scores, players_n_scores) |
            std::views::transform([](const auto& pair_of_pairs) {
                return std::tuple_cat(pair_of_pairs.first, pair_of_pairs.second);
            }))
    {
        auto winner = run_game(first_player, second_player);

        switch(winner)
        {
        case GameResult::PLAYER_1:
            first_player_score++;
            break;
        case GameResult::PLAYER_2:
            second_player_score++;
            break;
        default:
            break;
        }
    }
    return scores;
}

#endif