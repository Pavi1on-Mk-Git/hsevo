#include "logic/cards/HuntersMark.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned HUNTERS_MARK_NEW_HEALTH = 1;

std::vector<Game> HuntersMark::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.health = HUNTERS_MARK_NEW_HEALTH;
        entity.max_health = HUNTERS_MARK_NEW_HEALTH;
    });

    return resulting_states;
}