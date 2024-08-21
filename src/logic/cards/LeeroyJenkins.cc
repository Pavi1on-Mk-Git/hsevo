#include "logic/cards/LeeroyJenkins.h"

#include "logic/Game.h"
#include "logic/cards/Whelp.h"

const unsigned WHELP_COUNT = 2;
const auto WHELP = std::make_unique<Whelp>();

void LeeroyJenkins::on_play(Game& game, std::vector<OnPlayArg> args)
{
    static_cast<void>(args);

    for(unsigned i = 0; i < WHELP_COUNT; ++i)
        game.opponent().state.board.add_minion(Minion(*WHELP), game.opponent().state.board.minion_count());
}