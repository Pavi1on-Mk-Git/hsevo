#ifndef DECKLIST_H
#define DECKLIST_H

#include <vector>

#include "logic/cards/Card.h"
#include "logic/heroes/Hero.h"

using DecklistDeck = std::vector<std::pair<const Card*, unsigned>>;

struct Decklist
{
    const char* name;
    std::unique_ptr<Hero> hero;
    DecklistDeck cards_w_counts;

    Decklist(const char* name, std::unique_ptr<Hero> hero, DecklistDeck deck):
        name(name), hero(std::move(hero)), cards_w_counts(deck)
    {}
};

#endif