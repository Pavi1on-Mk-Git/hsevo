#include "Deck.h"

#include <algorithm>

Deck::Deck(const DeckList& decklist, std::ranlux24_base& random_engine): _random_engine(random_engine)
{
    std::transform(decklist.begin(), decklist.end(), std::back_inserter(deck_), [](const auto& card) {
        return std::make_unique<Card>(card);
    });
    shuffle();
}

Deck::Deck(const Deck& deck): _random_engine(deck._random_engine)
{
    std::transform(deck.deck_.begin(), deck.deck_.end(), std::back_inserter(deck_), [](const auto& card) {
        return std::make_unique<Card>(*card);
    });
}

void Deck::shuffle()
{
    std::shuffle(deck_.begin(), deck_.end(), _random_engine);
}

static const auto FATIGUE_DRAW = nullptr;

std::tuple<std::vector<std::unique_ptr<Card>>, unsigned> Deck::draw(unsigned amount)
{
    std::vector<std::unique_ptr<Card>> drawn_cards;
    int actual_amount = std::min<std::size_t>(amount, deck_.size());

    std::move(deck_.begin(), deck_.begin() + actual_amount, std::back_inserter(drawn_cards));
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
