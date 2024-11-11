#include "logic/Hand.h"

#include <algorithm>

Hand::Hand()
{
    hand_.reserve(MAX_HAND_SIZE);
}

void Hand::add_cards(const std::vector<const Card*>& cards)
{
    auto to_add = std::min(MAX_HAND_SIZE - hand_.size(), cards.size());
    std::ranges::copy(cards.begin(), cards.begin() + to_add, std::back_inserter(hand_));
}

void Hand::add_cards(const Card* card)
{
    if(hand_.size() != MAX_HAND_SIZE)
        hand_.push_back(card);
}

const Card* Hand::remove_card(unsigned position)
{
    auto to_return = hand_.at(position);
    hand_.erase(hand_.begin() + position);
    return to_return;
}

unsigned Hand::size() const
{
    return hand_.size();
}

const Card* const& Hand::get_card(unsigned position) const
{
    return hand_.at(position);
}

std::vector<const Card*>::const_iterator Hand::begin() const
{
    return hand_.begin();
}

std::vector<const Card*>::const_iterator Hand::end() const
{
    return hand_.end();
}
