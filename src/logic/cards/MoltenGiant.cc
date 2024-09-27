#include "logic/cards/MoltenGiant.h"

#include "logic/Game.h"

unsigned MoltenGiant::mana_cost(const Game& game) const
{
    const unsigned missing_health = game.current_player().hero->max_health - game.current_player().hero->health;
    return mana_cost_ > missing_health ? mana_cost_ - missing_health : 0;
}