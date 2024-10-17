#include "logic/Player.h"

Player::Player(const Decklist& decklist):
    hero(decklist.hero->clone()), mana_crystals(0), mana(0), deck(decklist.cards_w_counts)
{}

Player::Player(const Player& other):
    hero(other.hero->clone()), mana_crystals(other.mana_crystals), mana(other.mana), deck(other.deck), hand(other.hand),
    board(other.board)
{}
