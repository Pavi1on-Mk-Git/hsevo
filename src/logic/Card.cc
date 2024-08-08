#include "logic/Card.h"

#include "logic/Game.h"

void default_on_play(Game& game, std::vector<OnPlayArg> args)
{
    static_cast<void>(game);
    static_cast<void>(args);
}

std::vector<std::unique_ptr<PlayCardAction>> default_create_play_actions(
    const std::unique_ptr<Card>& self, Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    unsigned minion_count = game.current_player().state.board.minion_count();
    if(minion_count == Board::MAX_BOARD_SIZE || self->mana_cost > game.current_player().state.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayCardAction>(hand_position, board_position, self->mana_cost));

    return play_self_actions;
}

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const std::function<void(Game&, std::vector<OnPlayArg>)>& on_play_func,
    const std::function<std::vector<std::unique_ptr<PlayCardAction>>(const std::unique_ptr<Card>&, Game&, unsigned)>&
        create_play_actions_func,
    const MinionKeywords& keywords
):
    name(name),
    base_health(base_health), mana_cost(base_cost), attack(base_attack), health(base_health),
    on_play_func(on_play_func), create_play_actions_func(create_play_actions_func), keywords(keywords)
{}

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const MinionKeywords& keywords
):
    name(name),
    base_health(base_health), mana_cost(base_cost), attack(base_attack), health(base_health),
    on_play_func(default_on_play), create_play_actions_func(default_create_play_actions), keywords(keywords)
{}
