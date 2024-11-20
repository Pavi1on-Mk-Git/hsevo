#include "logic/cards/KillCommand.h"

#include "logic/Game.h"

const unsigned KILL_COMMAND_DMG = 3, KILL_COMMAND_DMG_WITH_BEAST = 5;

std::vector<Game> KillCommand::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    auto found_beast = std::ranges::find_if(game.current_player().board, [](const Minion& minion) {
        return minion.tribe == Tribe::BEAST;
    });

    const unsigned dmg_to_deal = (found_beast == game.current_player().board.end()) ? KILL_COMMAND_DMG :
                                                                                      KILL_COMMAND_DMG_WITH_BEAST;

    apply_to_entity(game, args, [&dmg_to_deal](Entity& entity) { entity.deal_dmg(dmg_to_deal); });

    return {game};
}