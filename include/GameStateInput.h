#ifndef GAME_STATE_INPUT_H
#define GAME_STATE_INPUT_H

#include <array>

#include "Board.h"

struct HeroStateInput
{
    unsigned health;
};

struct MinionStateInput
{
    unsigned health, attack;
};

struct PlayerStateInput
{
    HeroStateInput hero;
    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minions;
    unsigned hand_size, deck_size, mana;
};

struct GameStateInput
{
    std::array<PlayerStateInput, 2> players;
    std::array<std::array<double, 1 + 2 * Board::MAX_BOARD_SIZE + 3>, 2> get_evo_input() const;
};

#endif