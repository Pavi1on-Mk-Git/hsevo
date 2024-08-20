#include "logic/cards/MountainGiant.h"

#include "logic/Game.h"

unsigned MountainGiant::mana_cost(const Game& game) const
{
    const unsigned current_player_hand_size = game.current_player().state.hand.size();
    return mana_cost_ > current_player_hand_size ? mana_cost_ - current_player_hand_size : 0;
}