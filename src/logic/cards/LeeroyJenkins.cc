#include "logic/cards/LeeroyJenkins.h"

#include "logic/Game.h"
#include "logic/cards/Whelp.h"

const unsigned WHELP_COUNT = 2;

std::vector<Game> LeeroyJenkins::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    for(unsigned i = 0; i < WHELP_COUNT; ++i)
        game.add_minion(&Whelp::instance, game.opponent().board.minion_count(), false);

    return {game};
}