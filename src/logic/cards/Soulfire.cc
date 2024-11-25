#include "logic/cards/Soulfire.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned SOULFIRE_DMG = 4;

std::vector<Game> Soulfire::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [&game](Entity& entity) {
        entity.deal_dmg(SOULFIRE_DMG + game.current_player().spell_damage, game);
    });

    auto& hand = game.current_player().hand;

    if(hand.size() == 0)
        return resulting_states;

    std::vector<Game> post_discard_states;
    post_discard_states.reserve(hand.size());

    for(unsigned hand_position = 0; hand_position < hand.size(); ++hand_position)
    {
        Game game_copy(game);
        game_copy.current_player().hand.remove_card(hand_position);
        post_discard_states.push_back(game_copy);
    }

    return post_discard_states;
}