#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Hand.h"
#include "logic/heroes/Hero.h"
#include "players/PlayerLogic.h"
#include "utils/Rng.h"

struct SecretCard;

struct Player
{
    static constexpr unsigned MAX_MANA = 10;

    std::unique_ptr<Hero> hero;
    unsigned mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;
    std::vector<const SecretCard*> secrets;
    unsigned spell_damage;

    Player(const Decklist& decklist, Rng& rng);
    Player(const Player& other);
    Player& operator=(Player&& other) = default;
};

#endif