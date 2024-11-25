#include "logic/cards/SiphonSoul.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned SIPHON_SOUL_HEAL_AMOUNT = 3;

std::vector<Game> SiphonSoul::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });
    game.current_player().hero->restore_health(SIPHON_SOUL_HEAL_AMOUNT);

    return resulting_states;
}