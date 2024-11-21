#include "logic/cards/StarvingBuzzard.h"

#include "logic/Game.h"

void StarvingBuzzard::on_minion_summon(Game& game, Minion& minion, unsigned, unsigned player_id) const
{
    if(minion.tribe == Tribe::BEAST)
        game.draw(1, player_id);
}