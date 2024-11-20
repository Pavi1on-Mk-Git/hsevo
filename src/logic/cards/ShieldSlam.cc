#include "logic/cards/ShieldSlam.h"

#include "logic/Game.h"

std::vector<Game> ShieldSlam::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    const unsigned dmg_to_deal = game.current_player().hero->armour;

    apply_to_entity(game, args, [&dmg_to_deal](Entity& entity) { entity.deal_dmg(dmg_to_deal); });
    return {game};
}
