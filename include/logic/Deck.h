#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "logic/cards/Card.h"
#include "logic/decklists.h"

class Deck
{
private:
    std::vector<const Card*> deck_;
public:
    Deck(const DecklistDeck& decklist);
    void shuffle();
    std::pair<std::vector<const Card*>, unsigned> draw(unsigned amount);
    const Card* draw();
};

#endif
