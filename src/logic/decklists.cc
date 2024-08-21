#include "logic/decklists.h"

#include "logic/cards/BoulderfistOgre.h"

Decklist ogre_deck()
{
    Decklist decklist;

    decklist.emplace_back(std::make_unique<BoulderfistOgre>(), 30);

    return decklist;
}