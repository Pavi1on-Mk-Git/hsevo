#include "logic/cards/SingleArgTargetFriendlyMinionCard.h"

#include "logic/Game.h"

std::vector<std::unique_ptr<PlayCardAction>> SingleArgTargetFriendlyMinionCard::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().mana)
        return {};

    for(unsigned target_position = 0; target_position <= game.current_player().board.minion_count(); ++target_position)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{target_position})
        );

    return play_self_actions;
}