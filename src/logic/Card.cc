#include "logic/Card.h"

#include "logic/Game.h"

unsigned default_mana_cost(const std::unique_ptr<Card>& self, const Game& game)
{
    static_cast<void>(game);

    return self->mana_cost_;
}

void default_on_play(Game& game, std::vector<OnPlayArg> args)
{
    static_cast<void>(game);
    static_cast<void>(args);
}

std::vector<std::unique_ptr<PlayCardAction>> default_create_play_actions(
    const std::unique_ptr<Card>& self, const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned minion_count = game.current_player().state.board.minion_count();
    const unsigned mana_cost = self->mana_cost(self, game);

    if(minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().state.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayCardAction>(hand_position, board_position, mana_cost));

    return play_self_actions;
}

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const std::function<void(Game&, std::vector<OnPlayArg>)>& on_play_func,
    const std::function<
        std::vector<std::unique_ptr<PlayCardAction>>(const std::unique_ptr<Card>&, const Game&, unsigned)>&
        create_play_actions_func,
    const MinionKeywords& keywords
):

    name(name),
    mana_cost_(base_cost), base_health(base_health), attack(base_attack), health(base_health),
    mana_cost(default_mana_cost), on_play_func(on_play_func), create_play_actions_func(create_play_actions_func),
    keywords(keywords)
{}

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const MinionKeywords& keywords
):

    name(name),
    mana_cost_(base_cost), base_health(base_health), attack(base_attack), health(base_health),
    mana_cost(default_mana_cost), on_play_func(default_on_play), create_play_actions_func(default_create_play_actions),
    keywords(keywords)
{}

Card::Card(
    const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const std::function<unsigned(const std::unique_ptr<Card>&, const Game&)> mana_cost, const MinionKeywords& keywords
):

    name(name),
    mana_cost_(base_cost), base_health(base_health), attack(base_attack), health(base_health), mana_cost(mana_cost),
    on_play_func(default_on_play), create_play_actions_func(default_create_play_actions), keywords(keywords)
{}
