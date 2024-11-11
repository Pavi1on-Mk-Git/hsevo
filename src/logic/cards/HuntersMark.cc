#include "logic/cards/HuntersMark.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned HUNTERS_MARK_NEW_HEALTH = 1;

std::vector<Game> HuntersMark::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.health = HUNTERS_MARK_NEW_HEALTH;
        entity.max_health = HUNTERS_MARK_NEW_HEALTH;
    });

    return {game};
}