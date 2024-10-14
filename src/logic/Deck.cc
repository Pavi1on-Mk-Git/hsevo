#include "logic/Deck.h"

#include <algorithm>

#include "utils/Rng.h"

Deck::Deck(const DecklistDeck& decklist)
{
    for(const auto& [card, amount]: decklist)
        for(unsigned i = 0; i < amount; ++i)
            deck_.push_back(card->clone());
    shuffle();
}

Deck::Deck(const Deck& deck)
{
    for(const auto& card: deck.deck_)
        deck_.push_back(card->clone());
}

void Deck::shuffle()
{
    std::ranges::shuffle(deck_, Rng::instance()->generator());
}

static const auto FATIGUE_DRAW = nullptr;

std::pair<std::vector<std::unique_ptr<Card>>, unsigned> Deck::draw(unsigned amount)
{
    unsigned actual_amount = std::min<std::size_t>(amount, deck_.size());
    std::vector<std::unique_ptr<Card>> drawn_cards;
    drawn_cards.reserve(actual_amount);

    std::ranges::move(deck_.begin(), deck_.begin() + actual_amount, std::back_inserter(drawn_cards));
    deck_.erase(deck_.begin(), deck_.begin() + actual_amount);

    return {std::move(drawn_cards), amount - actual_amount};
}

std::unique_ptr<Card> Deck::draw()
{
    if(deck_.empty())
        return FATIGUE_DRAW;

    auto card = std::move(deck_.front());
    deck_.erase(deck_.begin());
    return card;
}
