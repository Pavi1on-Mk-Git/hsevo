#include "logic/cards/MortalCoil.h"

#include "logic/Entity.h"
#include "logic/Game.h"

std::vector<Game> MortalCoil::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.health -= 1;
        if(entity.health == 0)
            game.draw();
    });

    return {game};
}