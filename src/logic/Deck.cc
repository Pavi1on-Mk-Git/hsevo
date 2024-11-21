#include "logic/Deck.h"

#include <algorithm>

#include "utils/Rng.h"

Deck::Deck(const DecklistDeck& decklist)
{
    for(const auto& [card, amount]: decklist)
        for(unsigned i = 0; i < amount; ++i)
            deck_.push_back(card);
    shuffle();
}

void Deck::shuffle()
{
    std::ranges::shuffle(deck_, Rng::instance().generator());
}

std::pair<std::vector<HandCard>, unsigned> Deck::draw(unsigned amount)
{
    unsigned actual_amount = std::min<unsigned>(amount, deck_.size());
    std::vector<HandCard> drawn_cards(deck_.begin(), deck_.begin() + actual_amount);
    deck_.erase(deck_.begin(), deck_.begin() + actual_amount);

    return {drawn_cards, amount - actual_amount};
}

unsigned Deck::size() const
{
    return deck_.size();
}
