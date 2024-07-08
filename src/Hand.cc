#include "Hand.h"

#include <algorithm>

static constexpr auto MAX_HAND_SIZE = 10;

Hand::Hand()
{
    hand_.reserve(MAX_HAND_SIZE);
}

Hand::Hand(const Hand& hand)
{
    hand_.reserve(MAX_HAND_SIZE);
    std::transform(hand.hand_.begin(), hand.hand_.end(), std::back_inserter(hand_), [](const auto& card) {
        return std::make_unique<Card>(*card);
    });
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

std::unique_ptr<Card> Hand::remove_card(unsigned int position)
{
    auto to_return = std::move(hand_.at(position));
    hand_.erase(hand_.begin() + position);
    return to_return;
}

unsigned int Hand::size()
{
    return hand_.size();
}

std::unique_ptr<Card>& Hand::get_card(unsigned int position)
{
    return hand_.at(position);
}