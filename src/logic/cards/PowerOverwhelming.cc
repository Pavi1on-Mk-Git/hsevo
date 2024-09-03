#include "logic/cards/PowerOverwhelming.h"

#include "logic/Game.h"

std::vector<Game> PowerOverwhelming::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    auto target_position = std::get<unsigned>(args.at(0));

    auto& minion = game.current_player().hero.board.get_minion(target_position);
    minion.attack += 4;
    minion.max_health += 4;
    minion.health += 4;
    minion.will_die_horribly = true;

    return {game};
}
