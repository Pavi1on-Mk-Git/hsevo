#include "logic/cards/Armorsmith.h"

#include "logic/Game.h"

const unsigned ARMORSMITH_ARMOUR_INCREASE = 1;

void Armorsmith::on_minion_damaged(Game& game) const
{
    game.current_player().hero->armour += ARMORSMITH_ARMOUR_INCREASE;
}