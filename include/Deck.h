#ifndef DECK_H
#define DECK_H

#include <memory>
#include <random>
#include <vector>

#include "Card.h"
#include "decklists.h"

class Deck
{
private:
    std::ranlux24_base& _random_engine;
    std::vector<std::unique_ptr<Card>> _deck;
public:
    Deck(const DeckList& decklist, std::ranlux24_base& random_engine);
    void shuffle();
    std::vector<std::unique_ptr<Card>> draw(unsigned int amount);
    std::unique_ptr<Card> draw();
};

#endif
