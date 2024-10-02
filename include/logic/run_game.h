#ifndef RUN_GAME_H
#define RUN_GAME_H

#include "logic/Game.h"

GameResult run_game(
    const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player
);

#endif