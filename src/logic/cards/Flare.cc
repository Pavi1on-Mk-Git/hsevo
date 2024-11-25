#include "logic/cards/Flare.h"

#include "logic/Game.h"

std::vector<Game> Flare::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.opponent().secrets.clear();
    return resulting_states;
}
