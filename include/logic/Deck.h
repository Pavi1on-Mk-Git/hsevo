#ifndef DECK_H
#define DECK_H

#include <memory>
#include <random>
#include <vector>

#include "logic/cards/Card.h"
#include "logic/decklists.h"

class Deck
{
private:
    std::vector<std::unique_ptr<Card>> deck_;
public:
    Deck(const Decklist& decklist);
    Deck(const Deck& deck);
    void shuffle();
    std::tuple<std::vector<std::unique_ptr<Card>>, unsigned> draw(unsigned amount);
    std::unique_ptr<Card> draw();
};

#endif
