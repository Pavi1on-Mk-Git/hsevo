#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "Card.h"

class Hand
{
private:
    std::vector<std::unique_ptr<Card>> _hand;
public:
    void add_cards(std::vector<std::unique_ptr<Card>> cards);
    void add_cards(std::unique_ptr<Card> card);
    std::unique_ptr<Card> remove_card(unsigned int position);
    unsigned int size();
    std::unique_ptr<Card>& get_card(unsigned int position);
    Hand();
};

#endif