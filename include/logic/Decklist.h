#ifndef DECKLIST_H
#define DECKLIST_H

#include <vector>

#include "logic/cards/Card.h"
#include "logic/heroes/Hero.h"

using DecklistDeck = std::vector<std::pair<std::unique_ptr<Card>, unsigned>>;

struct Decklist
{
    std::unique_ptr<Hero> hero;
    DecklistDeck cards_w_counts;

    Decklist(std::unique_ptr<Hero> hero, DecklistDeck deck): hero(std::move(hero)), cards_w_counts(std::move(deck)) {}
};

#endif