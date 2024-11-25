#include "logic/cards/PowerOverwhelming.h"

#include "logic/Game.h"

const unsigned POWER_OVERWHELMING_BUFF_AMOUNT = 4;

std::vector<Game> PowerOverwhelming::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    const auto target_position = std::get<unsigned>(args.at(1));

    auto& minion = game.current_player().board.get_minion(target_position);
    minion.attack += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.max_health += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.health += POWER_OVERWHELMING_BUFF_AMOUNT;
    minion.will_die_horribly = true;

    return resulting_states;
}
