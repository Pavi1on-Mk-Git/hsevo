#ifndef DECKLIST_H
#define DECKLIST_H

#include <vector>

#include "logic/cards/Card.h"
#include "logic/heroes/Hero.h"

using DecklistDeck = std::vector<std::pair<const Card*, unsigned>>;

/**
 * Represents a decklist used in the game
 */
struct Decklist
{
    /**
     * Name of the decklist
     */
    const char* name;

    /**
     * Decklist's default hero
     */
    std::unique_ptr<Hero> hero;

    /**
     * Cards present in the decklist alongside their count
     */
    DecklistDeck cards_w_counts;

    /**
     * Construct a decklist
     * @param name Name of the decklist
     * @param hero Decklist's default hero
     * @param deck Cards present in the decklist alongside their count
     */
    Decklist(const char* name, std::unique_ptr<Hero> hero, DecklistDeck deck):
        name(name), hero(std::move(hero)), cards_w_counts(deck)
    {}
};

#endif