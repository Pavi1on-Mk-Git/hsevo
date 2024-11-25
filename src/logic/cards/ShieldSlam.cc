#include "logic/cards/ShieldSlam.h"

#include "logic/Game.h"

std::vector<Game> ShieldSlam::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    const unsigned dmg_to_deal = game.current_player().hero->armour;

    apply_to_entity(game, args, [&](Entity& entity) {
        entity.deal_dmg(dmg_to_deal + game.current_player().spell_damage, game);
    });
    return resulting_states;
}
