#include "logic/cards/Soulfire.h"

#include "logic/Entity.h"
#include "logic/Game.h"

std::vector<Game> Soulfire::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    apply_to_entity(game, args, [](Entity& entity) { entity.health -= 4; });

    auto& hand = game.current_player().hero.hand;

    std::vector<Game> post_discard_states;
    post_discard_states.reserve(hand.size());

    for(unsigned hand_position = 0; hand_position < hand.size(); ++hand_position)
    {
        Game game_copy(game);
        game_copy.current_player().hero.hand.remove_card(hand_position);
        post_discard_states.push_back(game_copy);
    }

    return post_discard_states;
}