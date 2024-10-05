#ifndef EVO_FUNCTIONS_HPP
#define EVO_FUNCTIONS_HPP

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

    for(unsigned i = 0; i < players.size(); ++i)
    {
        for(unsigned j = 0; j < players.size(); ++j)
        {
            auto winner = run_game(players.at(i), players.at(j));

            switch(winner)
            {
            case GameResult::PLAYER_1:
                scores.at(i)++;
                break;
            case GameResult::PLAYER_2:
                scores.at(j)++;
                break;
            default:
                break;
            }
        }
    }
    return scores;
}

#endif