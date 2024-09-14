#include "logic/Player.h"

Player::Player(std::shared_ptr<PlayerLogic> logic):
    logic(logic), hero(logic->decklist.hero->clone()), mana_crystals(0), mana(0), deck(logic->decklist.cards_w_counts)
{}

Player::Player(const Player& other):
    logic(other.logic), hero(other.hero->clone()), mana_crystals(other.mana_crystals), mana(other.mana),
    deck(other.deck), hand(other.hand), board(other.board)
{}