#include "logic/cards/Coin.h"

#include "logic/Game.h"

const unsigned COIN_MANA_INCREASE = 1;

std::vector<Game> Coin::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    auto& current_mana = game.current_player().mana;

    if(current_mana < Player::MAX_MANA)
        current_mana += COIN_MANA_INCREASE;

    return resulting_states;
}