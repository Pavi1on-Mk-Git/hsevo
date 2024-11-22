#include "logic/cards/ShieldBlock.h"

#include "logic/Game.h"

const unsigned SHIELD_BLOCK_ARMOUR = 5;

std::vector<Game> ShieldBlock::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().hero->armour += SHIELD_BLOCK_ARMOUR;
    game.draw();

    return {game};
}
