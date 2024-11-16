#include "logic/cards/Flare.h"

#include "logic/Game.h"

std::vector<Game> Flare::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.opponent().secrets.clear();
    return {game};
}
