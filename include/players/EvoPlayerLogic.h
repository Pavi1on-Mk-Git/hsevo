#ifndef EVO_PLAYER_LOGIC_H
#define EVO_PLAYER_LOGIC_H

#include "ai/SimpleEvo.hpp"
#include "logic/Board.h"
#include "players/PlayerLogic.h"

struct EvoPlayerLogic: PlayerLogic
{
    SimpleEvo<GameStateInput::INPUT_SIZE> evo;
    EvoPlayerLogic(const Decklist& decklist, SimpleEvo<GameStateInput::INPUT_SIZE> evo);
    double add_game_score(double sum, const Game& game) const;
    double average_of_states(const std::vector<Game>& states) const;
    Game choose_and_apply_action(const Game& game, std::vector<std::unique_ptr<Action>> actions) const override;
};

#endif