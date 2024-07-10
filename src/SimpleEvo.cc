#include "SimpleEvo.hpp"

#include "EvoPlayerLogic.h"
#include "Game.h"

std::vector<unsigned> score_member(
    const std::vector<SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>>& population, const DeckList& decklist
)
{
    std::vector<unsigned> scores;
    for(unsigned member_index = 0; member_index < population.size(); ++member_index)
        scores.push_back(0);

    std::vector<std::unique_ptr<PlayerLogic>> players;
    for(const auto& member: population)
        players.push_back(std::make_unique<EvoPlayerLogic>(decklist, member));

    for(unsigned i = 0; i < players.size(); ++i)
    {
        for(unsigned j = 0; j < players.size(); ++j)
        {
            auto game = Game(players.at(i), players.at(j));
            auto winner = game.run();

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