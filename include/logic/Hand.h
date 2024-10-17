#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "logic/cards/Card.h"

class Hand
{
private:
    std::vector<const Card*> hand_;
public:
    void add_cards(const std::vector<const Card*>& cards);
    void add_cards(const Card* card);
    const Card* remove_card(unsigned position);
    unsigned size() const;
    const Card* const& get_card(unsigned position) const;
    Hand();
};

#endif