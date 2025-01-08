#include "logic/cards/ArcaneGolem.h"

#include "logic/Game.h"

const unsigned ARCANE_GOLEM_MANA_INCREASE = 1;

std::vector<Game> ArcaneGolem::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    auto& opponent_mana = game.opponent().mana_crystals;

    if(opponent_mana < Player::MAX_MANA)
        opponent_mana += ARCANE_GOLEM_MANA_INCREASE;

    return resulting_states;
}