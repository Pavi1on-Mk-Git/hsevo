#include "logic/cards/PowerOverwhelming.h"

#include "logic/Game.h"

const unsigned POWER_OVERWHELMING_BUFF_AMOUNT = 4;

std::vector<Game> PowerOverwhelming::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    const auto target_position = std::get<unsigned>(args.at(0));

    auto& minion = game.current_player().board.get_minion(target_position);
    minion.attack += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.max_health += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.health += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.will_die_horribly = true;

    return {game};
}
