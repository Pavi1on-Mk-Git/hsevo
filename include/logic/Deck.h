#ifndef DECK_H
#define DECK_H

#include <memory>
#include <optional>
#include <vector>

#include "logic/Decklist.h"
#include "logic/cards/Card.h"
#include "logic/cards/HandCard.h"
#include "utils/Rng.h"

/**
 * Represents a player's deck of cards
 */
class Deck
{
private:
    /**
     * Underlying collection of cards
     */
    std::vector<const Card*> deck_;
public:
    /**
     * Create a deck containing cards specified in a decklist and shuffle it randomly
     */
    Deck(const DecklistDeck& decklist, Rng& rng);

    /**
     * Draw cards from the deck
     * @param amount Amount of cards to draw
     * @return Vector of drawn cards and number of additional cards which could not have been drawn if the deck got
     * emptied
     */
    std::pair<std::vector<HandCard>, unsigned> draw(unsigned amount);

    /**
     * Return the amount of cards left in the deck
     * @return Deck size
     */
    unsigned size() const;

    /**
     * Look at the top card in the deck without drawing it
     * @param position Offset from the top of the deck of the peeked card
     * @return Card from the top of the deck
     */
    const Card* const& peek(unsigned position) const;
};

#endif
