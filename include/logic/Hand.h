#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "logic/cards/HandCard.h"

class Hand
{
private:
    std::vector<HandCard> hand_;
public:
    static constexpr unsigned MAX_HAND_SIZE = 10;

    Hand();
    void add_cards(const std::vector<HandCard>& cards);
    void add_cards(const HandCard card);
    HandCard remove_card(unsigned position);
    unsigned size() const;
    const HandCard& get_card(unsigned position) const;
    std::vector<HandCard>::const_iterator begin() const;
    std::vector<HandCard>::const_iterator end() const;
};

#endif