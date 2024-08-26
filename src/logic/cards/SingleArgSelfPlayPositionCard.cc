#include "logic/cards/SingleArgSelfPlayPositionCard.h"

#include "logic/Game.h"

std::vector<std::unique_ptr<PlayCardAction>> SingleArgSelfPlayPositionCard::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned minion_count = game.current_player().state.board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().state.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{board_position}
        ));

    return play_self_actions;
}