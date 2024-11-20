#include "logic/cards/MortalCoil.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned MORTAL_COIL_DMG = 1;

std::vector<Game> MortalCoil::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.deal_dmg(MORTAL_COIL_DMG);
        if(entity.health == 0)
            game.draw();
    });

    return {game};
}