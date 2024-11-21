#include "logic/cards/Slam.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned SLAM_DMG = 2;

std::vector<Game> Slam::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.deal_dmg(SLAM_DMG, game);
        if(entity.health > 0)
            game.draw();
    });

    return {game};
}