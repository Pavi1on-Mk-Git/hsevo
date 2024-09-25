#ifndef RUN_GAME_H
#define RUN_GAME_H

#include "logic/Game.h"

GameResult run_game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player);

#endif