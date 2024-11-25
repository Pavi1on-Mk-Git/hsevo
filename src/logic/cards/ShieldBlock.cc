#include "logic/cards/ShieldBlock.h"

#include "logic/Game.h"

const unsigned SHIELD_BLOCK_ARMOUR = 5;

std::vector<Game> ShieldBlock::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.current_player().hero->armour += SHIELD_BLOCK_ARMOUR;
    game.draw();

    return resulting_states;
}
