#include "Deck.h"

#include <algorithm>

Deck::Deck(const DeckList& decklist, std::ranlux24_base& random_engine): _random_engine(random_engine)
{
    std::transform(decklist.begin(), decklist.end(), std::back_inserter(_deck), [](const auto& card) {
        return std::make_unique<Card>(card);
    });
    shuffle();
}

void Deck::shuffle()
{
    std::shuffle(_deck.begin(), _deck.end(), _random_engine);
}

static const auto fatigue_draw = nullptr;

std::vector<std::unique_ptr<Card>> Deck::draw(unsigned int amount)
{
    std::vector<std::unique_ptr<Card>> drawn_cards;
    int actual_amount = std::min<std::size_t>(amount, _deck.size());

    std::move(_deck.begin(), _deck.begin() + actual_amount, std::back_inserter(drawn_cards));
    _deck.erase(_deck.begin(), _deck.begin() + actual_amount);

    std::fill_n(std::back_inserter(_deck), amount - actual_amount, fatigue_draw);

    return drawn_cards;
}

std::unique_ptr<Card> Deck::draw()
{
    if(_deck.empty())
        return fatigue_draw;

    auto card = std::move(_deck.front());
    _deck.erase(_deck.begin());
    return card;
}
