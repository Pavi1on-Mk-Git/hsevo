#include "logic/cards/Slam.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned SLAM_DMG = 2;

std::vector<Game> Slam::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.deal_dmg(SLAM_DMG + game.current_player().spell_damage, game);
        if(entity.health > 0)
            game.draw();
    });

    return resulting_states;
}