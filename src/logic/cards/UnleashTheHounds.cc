#include "logic/cards/UnleashTheHounds.h"

#include "logic/Game.h"
#include "logic/cards/Hound.h"

std::vector<Game> UnleashTheHounds::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    unsigned current_minion_count = game.current_player().board.minion_count();
    unsigned opponent_minion_count = game.opponent().board.minion_count();

    unsigned summon_count = opponent_minion_count > current_minion_count ?
                                opponent_minion_count - current_minion_count :
                                1;

    for(unsigned summon_offset = 0; summon_offset < summon_count; ++summon_offset)
    {
        game.add_minion(&Hound::instance, current_minion_count + summon_offset);
    }

    return resulting_states;
}