#ifndef DECK_H
#define DECK_H

#include <memory>
#include <optional>
#include <vector>

#include "logic/Decklist.h"
#include "logic/cards/Card.h"
#include "logic/cards/HandCard.h"

class Deck
{
private:
    std::vector<const Card*> deck_;
public:
    Deck(const DecklistDeck& decklist);
    void shuffle();
    std::pair<std::vector<HandCard>, unsigned> draw(unsigned amount);
    unsigned size() const;
};

#endif
