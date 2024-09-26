#include "logic/cards/Coin.h"

#include "logic/Game.h"

const unsigned COIN_MANA_INCREASE = 1;

std::vector<Game> Coin::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(args);

    auto& current_mana = game.current_player().mana;

    if(current_mana < Player::MAX_MANA)
        current_mana += COIN_MANA_INCREASE;

    return {game};
}