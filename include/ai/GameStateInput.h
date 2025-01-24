#ifndef GAME_STATE_INPUT_H
#define GAME_STATE_INPUT_H

#include <array>

#include "logic/Board.h"

/**
 * Neural network input collected from a Hero
 */
struct HeroStateInput
{
    /**
     * Health of the hero
     */
    int health;

    /**
     * Armour of the hero
     */
    unsigned armour;

    /**
     * Whether or not the hero can currently attack
     */
    bool can_attack;

    /**
     * Statistics of the weapon worn by hero (0 if no weapon is currently being used)
     */
    unsigned weapon_attack, weapon_durability;
};

/**
 * Neural network input collected from a Minion
 */
struct MinionStateInput
{
    /**
     * Health of the minion
     */
    int health;

    /**
     * Attack of the minion
     */
    unsigned attack;

    /**
     * Whether or not the minion can currently attack
     */
    bool can_attack;

    /**
     * Whether or not the minion has the taunt keyword
     */
    bool has_taunt;

    /**
     * Whether or not the minion has a deathrattle
     */
    bool has_deathrattle;

    /**
     * Whether or not the minion has an end-of-turn effect
     */
    bool has_eot;
};

/**
 * Input collected from a Player
 */
struct PlayerInput
{
    /**
     * Input of the player's hero
     */
    HeroStateInput hero;

    /**
     * Input of each of the player's minions
     */
    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minions;

    /**
     * Other statistics of the player
     */
    unsigned hand_size, deck_size, mana, secret_count;
};

/**
 * Input collected from a Game
 */
struct GameStateInput
{
    /**
     * Total size of the input (To be updated when parts of this class change)
     */
    static constexpr unsigned INPUT_SIZE = 5 + 6 * Board::MAX_BOARD_SIZE + 4;

    /**
     * Input of both players
     */
    std::array<PlayerInput, 2> players;

    /**
     * Convert the game state input into an array of values to be inserted into a neural network
     *
     * @return Array of values to be inserted into a neural network
     */
    std::array<std::array<double, INPUT_SIZE>, 2> get_evo_input() const;
};

#endif