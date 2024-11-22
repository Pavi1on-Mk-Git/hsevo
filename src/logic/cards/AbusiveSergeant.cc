#include "logic/cards/AbusiveSergeant.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned ABUSIVE_SERGEANT_BUFF_AMOUNT = 2;

std::vector<Game> AbusiveSergeant::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    using enum TargetType;

    if(!args.empty())
    {
        const auto target_type = std::get<TargetType>(args.at(0));
        const auto target_position = std::get<unsigned>(args.at(1));

        switch(target_type)
        {
        case ALLY_MINION:
            game.current_player().board.get_minion(target_position).attack += ABUSIVE_SERGEANT_BUFF_AMOUNT;
            break;
        case ENEMY_MINION:
            game.opponent().board.get_minion(target_position).attack += ABUSIVE_SERGEANT_BUFF_AMOUNT;
            break;
        default:
            break;
        }
    }

    return {game};
}
