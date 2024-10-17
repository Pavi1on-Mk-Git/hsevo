#include "logic/cards/TwilightDrake.h"

#include "logic/Game.h"

std::vector<Game> TwilightDrake::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    const auto position_played = std::get<unsigned>(args.at(0));
    auto& self = game.current_player().board.get_minion(position_played);
    const auto hand_size = game.current_player().hand.size();
    self.health += hand_size;
    self.max_health += hand_size;

    return {game};
}