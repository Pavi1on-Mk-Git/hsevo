#include "logic/cards/SiphonSoul.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned SIPHON_SOUL_HEAL_AMOUNT = 3;

std::vector<Game> SiphonSoul::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });
    game.current_player().hero->restore_health(SIPHON_SOUL_HEAL_AMOUNT);

    return {game};
}