#include "logic/cards/StarvingBuzzard.h"

#include "logic/Game.h"

void StarvingBuzzard::on_minion_summon(Game& game, Minion& minion, unsigned) const
{
    if(minion.tribe == Tribe::BEAST)
    {
        game.draw();
    }
}