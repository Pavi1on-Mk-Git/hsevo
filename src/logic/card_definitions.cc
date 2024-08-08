#include "logic/card_definitions.h"

#include "logic/Game.h"

const Card BOULDERFIST_OGRE("Boulderfist Ogre", 6, 6, 7);
const Card ANCIENT_WATCHER("Ancient Watcher", 2, 4, 5, CANT_ATTACK);

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

const Card SUNFURY_PROTECTOR(
    "Sunfury Protector", 2, 2, 3, sunfury_protector_on_play, sunfury_protector_create_play_actions
);

void earthen_ring_farseer_on_play(Game& game, std::vector<OnPlayArg> args)
{
    auto target_friendly = std::get<bool>(args.at(0));
    auto target_position = std::get<unsigned>(args.at(1));
    auto heal_amount = std::get<unsigned>(args.at(2));

    if(target_friendly)
        game.current_player().state.board.get_minion(target_position).restore_health(heal_amount);
    else
        game.opponent().state.board.get_minion(target_position).restore_health(heal_amount);
}

const unsigned EARTHEN_FARSEER_HEAL_AMOUNT = 3;

std::vector<std::unique_ptr<PlayCardAction>> earthen_ring_farseer_create_play_actions(
    const std::unique_ptr<Card>& self, Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    unsigned minion_count = game.current_player().state.board.minion_count();
    if(minion_count == Board::MAX_BOARD_SIZE || self->mana_cost > game.current_player().state.mana)
        return {};

    for(const auto& player: {game.current_player(), game.opponent()})
    {
        for(unsigned board_position = 0; board_position <= player.state.board.minion_count(); ++board_position)
            play_self_actions.push_back(std::make_unique<PlayCardAction>(
                hand_position, board_position, self->mana_cost,
                std::vector<OnPlayArg>{&player == &game.current_player(), board_position, EARTHEN_FARSEER_HEAL_AMOUNT}
            ));
    }

    return play_self_actions;
}

const Card EARTHEN_RING_FARSEER(
    "Earthen Ring, Farseer", 3, 3, 3, earthen_ring_farseer_on_play, earthen_ring_farseer_create_play_actions
);