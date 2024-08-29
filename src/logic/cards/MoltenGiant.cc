#include "logic/cards/MoltenGiant.h"

#include "logic/Game.h"

unsigned MoltenGiant::mana_cost(const Game& game) const
{
    const unsigned current_player_health = game.current_player().hero.health;
    return mana_cost_ > current_player_health ? mana_cost_ - current_player_health : 0;
}