#ifndef DECK_H
#define DECK_H

#include <memory>
#include <optional>
#include <vector>

#include "logic/Decklist.h"
#include "logic/cards/Card.h"
#include "logic/cards/HandCard.h"
#include "utils/Rng.h"

class Deck
{
private:
    std::vector<const Card*> deck_;
public:
    Deck(const DecklistDeck& decklist, Rng& rng);
    void shuffle(Rng& rng);
    std::pair<std::vector<HandCard>, unsigned> draw(unsigned amount);
    unsigned size() const;
};

#endif
