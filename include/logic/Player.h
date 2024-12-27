#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Hand.h"
#include "logic/heroes/Hero.h"
#include "players/PlayerLogic.h"
#include "utils/Rng.h"

struct SecretCard;

/**
 * Represents a player in the game
 */
struct Player
{
    /**
     * Maximum amount of mana which a player can have at once
     */
    static constexpr unsigned MAX_MANA = 10;

    /**
     * Hero used by the player
     */
    std::unique_ptr<Hero> hero;

    /**
     * Mana crystals and remaining mana
     */
    unsigned mana_crystals, mana;

    /**
     * Player's deck
     */
    Deck deck;

    /**
     * Player's hand
     */
    Hand hand;

    /**
     * Player's board
     */
    Board board;

    /**
     * Active secrets played by the player
     */
    std::vector<const SecretCard*> secrets;

    /**
     * Amount of bonus spell damage
     */
    unsigned spell_damage;

    /**
     * Construct a default player from a decklist
     * @param decklist Decklist of the player
     * @param rng Source of randomness
     */
    Player(const Decklist& decklist, Rng& rng);

    Player(const Player& other);
    Player& operator=(Player&& other) = default;
};

#endif