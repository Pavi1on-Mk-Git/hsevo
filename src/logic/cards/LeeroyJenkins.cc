#include "logic/cards/LeeroyJenkins.h"

#include "logic/Game.h"
#include "logic/cards/Whelp.h"

const unsigned WHELP_COUNT = 2;

std::vector<Game> LeeroyJenkins::on_play(Game& game, const std::vector<OnPlayArg>&)
{
    for(unsigned i = 0; i < WHELP_COUNT; ++i)
        game.opponent().board.add_minion(Whelp(), game.opponent().board.minion_count());

    return {game};
}