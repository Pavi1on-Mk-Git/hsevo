#include "logic/cards/TwilightDrake.h"

#include "logic/Game.h"

std::vector<Game> TwilightDrake::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    const auto position_played = std::get<unsigned>(args.at(0));
    auto& self = game.current_player().hero.board.get_minion(position_played);
    const auto hand_size = game.current_player().hero.hand.size();
    self.health += hand_size;
    self.max_health += hand_size;

    return {game};
}