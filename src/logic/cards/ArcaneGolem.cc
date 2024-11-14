#include "logic/cards/ArcaneGolem.h"

#include "logic/Game.h"

const unsigned ARCANE_GOLEM_MANA_INCREASE = 1;

std::vector<Game> ArcaneGolem::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.opponent().mana_crystals += ARCANE_GOLEM_MANA_INCREASE;

    return {game};
}