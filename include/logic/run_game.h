#ifndef RUN_GAME_H
#define RUN_GAME_H

#include "logic/Game.h"
#include "utils/Rng.h"

/**
 * Run a simulation of a game with provided players
 * @param first_player First player
 * @param second_player Second player
 * @param rng Source of randomness
 * @return Game result
 */
GameResult run_game(
    const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player, Rng& rng
);

#endif