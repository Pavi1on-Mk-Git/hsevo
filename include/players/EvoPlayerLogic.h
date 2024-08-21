#ifndef EVO_PLAYER_LOGIC_H
#define EVO_PLAYER_LOGIC_H

#include "ai/SimpleEvo.hpp"
#include "logic/Board.h"
#include "players/PlayerLogic.h"

struct EvoPlayerLogic: PlayerLogic
{
    SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3> evo;
    EvoPlayerLogic(const Decklist& decklist, SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3> evo);
    std::unique_ptr<Action> choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
        const override;
};

#endif