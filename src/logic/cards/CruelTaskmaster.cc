#include "logic/cards/CruelTaskmaster.h"

#include "logic/Game.h"

const unsigned CRUEL_TASKMASTER_DMG = 1, CRUEL_TASKMASTER_BUFF_AMOUNT = 2;

std::vector<Game> CruelTaskmaster::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    using enum TargetType;

    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    if(!args.empty())
    {
        const auto target_type = std::get<TargetType>(args.at(0));
        const auto target_position = std::get<unsigned>(args.at(1));

        auto dmg_and_buff = [&game](Minion& minion) {
            minion.deal_dmg(CRUEL_TASKMASTER_DMG, game);
            minion.attack += CRUEL_TASKMASTER_BUFF_AMOUNT;
        };

        switch(target_type)
        {
        case ALLY_MINION:
            dmg_and_buff(game.current_player().board.get_minion(target_position));
            break;
        case ENEMY_MINION:
            dmg_and_buff(game.opponent().board.get_minion(target_position));
            break;

        default:
            break;
        }
    }

    return resulting_states;
}