#include "logic/cards/Card.h"

#include "logic/Game.h"

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const MinionKeywords& keywords
):

    mana_cost_(base_cost),
    name(name), base_attack(base_attack), base_health(base_health), keywords(keywords)
{}

unsigned Card::mana_cost(const Game& game) const
{
    static_cast<void>(game);

    return mana_cost_;
}

void Card::on_play(Game& game, std::vector<OnPlayArg> args)
{
    static_cast<void>(game);
    static_cast<void>(args);
}

std::vector<std::unique_ptr<PlayCardAction>> Card::create_play_actions(const Game& game, unsigned hand_position)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned minion_count = game.current_player().state.board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().state.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayCardAction>(hand_position, board_position, mana_cost));

    return play_self_actions;
}
