#include "logic/cards/Soulfire.h"

#include "logic/Entity.h"
#include "logic/Game.h"

std::vector<Game> Soulfire::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    auto after_dmg_states = apply_to_entity(game, args, [](Entity& entity) { entity.health -= 4; });

    std::vector<Game> post_discard_states;

    for(auto& state: after_dmg_states)
        for(unsigned hand_position = 0; hand_position < state.current_player().hero.hand.size(); ++hand_position)
        {
            Game state_copy(state);
            state_copy.current_player().hero.hand.remove_card(hand_position);
            post_discard_states.push_back(state_copy);
        }

    return post_discard_states;
}