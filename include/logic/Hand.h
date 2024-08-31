#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "logic/cards/Card.h"

class Hand
{
private:
    std::vector<std::unique_ptr<Card>> hand_;
public:
    void add_cards(std::vector<std::unique_ptr<Card>> cards);
    void add_cards(std::unique_ptr<Card> card);
    std::unique_ptr<Card> remove_card(unsigned position);
    unsigned size() const;
    const std::unique_ptr<Card>& get_card(unsigned position) const;
    Hand();
    Hand(const Hand& hand);
    Hand& operator=(Hand&& other) = default;
};

#endif