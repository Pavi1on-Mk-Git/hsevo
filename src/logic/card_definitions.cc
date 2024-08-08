#include "logic/card_definitions.h"

#include "logic/Game.h"

const Card BOULDERFIST_OGRE = Card("Boulderfist Ogre", 6, 6, 7);
const Card ANCIENT_WATCHER = Card("Ancient Watcher", 2, 4, 5, CANT_ATTACK);

void sunfury_protector_on_play(Game& game, std::vector<OnPlayArg> args)
{
    auto position_played = std::get<unsigned>(args.at(0));

    for(unsigned board_position = std::max(position_played - 1, 0u);
        board_position < std::min(game.current_player().state.hand.size(), position_played + 1); ++board_position)
        game.current_player().state.board.get_minion(board_position).keywords |= TAUNT;
}

std::vector<std::unique_ptr<PlayCardAction>> sunfury_protector_create_play_actions(
    const std::unique_ptr<Card>& self, Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    unsigned minion_count = game.current_player().state.board.minion_count();
    if(minion_count == Board::MAX_BOARD_SIZE || self->mana_cost > game.current_player().state.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayCardAction>(
            hand_position, board_position, self->mana_cost, std::vector<OnPlayArg>{board_position}
        ));

    return play_self_actions;
}

const Card SUNFURY_PROTECTOR = Card(
    "Sunfury Protector", 2, 2, 3, sunfury_protector_on_play, sunfury_protector_create_play_actions
);