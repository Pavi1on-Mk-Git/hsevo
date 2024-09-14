#include "logic/decklists.h"

#include "logic/cards/BoulderfistOgre.h"
#include "logic/heroes/GulDan.h"

Decklist ogre_deck()
{
    std::unique_ptr<Hero> hero = std::make_unique<GulDan>();

    DecklistDeck deck;
    deck.emplace_back(std::make_unique<BoulderfistOgre>(), 30);

    return Decklist(std::move(hero), std::move(deck));
}