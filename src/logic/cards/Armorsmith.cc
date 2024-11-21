#include "logic/cards/Armorsmith.h"

#include "logic/Game.h"

const unsigned ARMORSMITH_ARMOUR_INCREASE = 1;

void Armorsmith::on_minion_damaged(Game& game, unsigned player_id) const
{
    game.players.at(player_id).hero->armour += ARMORSMITH_ARMOUR_INCREASE;
}