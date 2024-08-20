#include "logic/cards/TwilightDrake.h"

#include "logic/Game.h"

void TwilightDrake::on_play(Game& game, std::vector<OnPlayArg> args)
{
    const auto position_played = std::get<unsigned>(args.at(0));
    auto& self = game.current_player().state.board.get_minion(position_played);
    const auto hand_size = game.current_player().state.hand.size();
    self.health += hand_size;
    self.max_health += hand_size;
}