#include "logic/cards/AcolyteOfPain.h"

#include "logic/Game.h"

void AcolyteOfPain::on_damaged(Game& game, unsigned player_id) const
{
    game.draw(1, player_id);
}