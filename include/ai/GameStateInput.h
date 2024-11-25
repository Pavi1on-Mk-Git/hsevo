#ifndef GAME_STATE_INPUT_H
#define GAME_STATE_INPUT_H

#include <array>

#include "logic/Board.h"

struct HeroStateInput
{
    int health;
    bool can_attack;
    unsigned weapon_attack, weapon_durability;
};

struct MinionStateInput
{
    int health;
    unsigned attack;
    bool can_attack;
    bool has_taunt;
    bool has_deathrattle;
    bool has_eot;
};

struct HeroInput
{
    HeroStateInput hero;
    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minions;
    unsigned hand_size, deck_size, mana, secret_count;
};

struct GameStateInput
{
    static constexpr unsigned INPUT_SIZE = 4 + 6 * Board::MAX_BOARD_SIZE + 4;
    std::array<HeroInput, 2> players;
    std::array<std::array<double, INPUT_SIZE>, 2> get_evo_input() const;
};

#endif