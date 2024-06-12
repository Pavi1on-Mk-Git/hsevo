#include "Hand.h"

#include <algorithm>

static constexpr auto MAX_HAND_SIZE = 10;

Hand::Hand()
{
    _hand.reserve(MAX_HAND_SIZE);
}

Hand::Hand(const Hand& hand)
{
    _hand.reserve(MAX_HAND_SIZE);
    std::transform(hand._hand.begin(), hand._hand.end(), std::back_inserter(_hand), [](const auto& card) {
        return std::make_unique<Card>(*card);
    });
}

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

std::unique_ptr<Card> Hand::remove_card(unsigned int position)
{
    auto to_return = std::move(_hand.at(position));
    _hand.erase(_hand.begin() + position);
    return to_return;
}

unsigned int Hand::size()
{
    return _hand.size();
}

std::unique_ptr<Card>& Hand::get_card(unsigned int position)
{
    return _hand.at(position);
}