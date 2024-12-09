#include "logic/Player.h"

Player::Player(const Decklist& decklist, Rng& rng):
    hero(decklist.hero->clone()), mana_crystals(0), mana(0), deck(decklist.cards_w_counts, rng), spell_damage(0)
{}

Player::Player(const Player& other):
    hero(other.hero->clone()), mana_crystals(other.mana_crystals), mana(other.mana), deck(other.deck), hand(other.hand),
    board(other.board), secrets(other.secrets), spell_damage(other.spell_damage)
{}
