#include "logic/cards/LeeroyJenkins.h"

#include "logic/Game.h"
#include "logic/cards/Whelp.h"

const unsigned WHELP_COUNT = 2;

std::vector<Game> LeeroyJenkins::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(args);

    for(unsigned i = 0; i < WHELP_COUNT; ++i)
        game.opponent().hero.board.add_minion(Minion(Whelp()), game.opponent().hero.board.minion_count());

    return {game};
}