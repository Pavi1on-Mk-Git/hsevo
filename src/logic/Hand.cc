#include "logic/Hand.h"

#include <algorithm>

static const unsigned MAX_HAND_SIZE = 10;

Hand::Hand()
{
    hand_.reserve(MAX_HAND_SIZE);
}

Hand::Hand(const Hand& hand)
{
    hand_.reserve(MAX_HAND_SIZE);
    for(const auto& card: hand.hand_)
        hand_.push_back(card->clone());
}

void Hand::add_cards(std::vector<std::unique_ptr<Card>> cards)
{
    auto to_add = std::min(MAX_HAND_SIZE - hand_.size(), cards.size());
    std::move(cards.begin(), cards.begin() + to_add, std::back_inserter(hand_));
}

void Hand::add_cards(std::unique_ptr<Card> card)
{
    if(hand_.size() != MAX_HAND_SIZE)
        hand_.push_back(std::move(card));
}

std::unique_ptr<Card> Hand::remove_card(unsigned position)
{
    auto to_return = std::move(hand_.at(position));
    hand_.erase(hand_.begin() + position);
    return to_return;
}

unsigned Hand::size() const
{
    return hand_.size();
}

std::unique_ptr<Card>& Hand::get_card(unsigned position)
{
    return hand_.at(position);
}