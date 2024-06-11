#include "Hand.h"

Hand::Hand(): _hand()
{
    _hand.reserve(10);
}

static constexpr auto MAX_HAND_SIZE = 10;

void Hand::add_cards(std::vector<std::unique_ptr<Card>> cards)
{
    auto to_add = std::min(MAX_HAND_SIZE - _hand.size(), cards.size());
    std::move(cards.begin(), cards.begin() + to_add, std::back_inserter(_hand));
}

void Hand::add_cards(std::unique_ptr<Card> card)
{
    if(_hand.size() != MAX_HAND_SIZE)
        _hand.push_back(std::move(card));
}