#include "logic/cards/UnleashTheHounds.h"

#include "logic/Game.h"
#include "logic/cards/Hound.h"

std::vector<Game> UnleashTheHounds::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    unsigned current_minion_count = game.current_player().board.minion_count();

    unsigned summon_count = game.opponent().board.minion_count() - current_minion_count;

    for(unsigned summon_offset = 0; summon_offset < summon_count; ++summon_offset)
    {
        game.add_minion(&Hound::instance, current_minion_count + summon_offset);
    }

    return {game};
}