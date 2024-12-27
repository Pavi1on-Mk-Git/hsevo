#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "logic/cards/HandCard.h"

/**
 * Represents a player's hand of cards in the game
 */
class Hand
{
private:
    /**
     * Underlying collection of hand cards
     */
    std::vector<HandCard> hand_;
public:
    /**
     * Maximum amount of cards possible to be held at once
     */
    static constexpr unsigned MAX_HAND_SIZE = 10;

    /**
     * Construct an empty hand
     */
    Hand();

    /**
     * Add a vector of cards to the hand
     * @param cards Cards to add
     */
    void add_cards(const std::vector<HandCard>& cards);

    /**
     * Add a card to the hand
     * @param card Card to add
     */
    void add_cards(const HandCard card);

    /**
     * Remove a card from the hand
     * @param position Position of the card to be removed
     * @return Removed card
     */
    HandCard remove_card(unsigned position);

    /**
     * Return the amount cards currently present in the hand of the player
     * @return Hand size
     */
    unsigned size() const;

    /**
     * Get a card from the hand without removing it
     * @param position Position of the card
     * @return Selected card
     */
    const HandCard& get_card(unsigned position) const;
    std::vector<HandCard>::const_iterator begin() const;
    std::vector<HandCard>::const_iterator end() const;
};

#endif
