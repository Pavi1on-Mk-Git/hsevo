#include "logic/cards/MinionCard.h"

#include "logic/Game.h"

MinionCard::MinionCard(std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health)
{}

MinionCard::MinionCard(
    std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health,
    const MinionKeywords& keywords
):
    Card(name, base_cost),
    base_attack(base_attack), base_health(base_health), keywords(keywords)
{}

MinionCard::MinionCard(
    std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health, const Tribe& tribe
):
    Card(name, base_cost),
    base_attack(base_attack), base_health(base_health), tribe(tribe)
{}

std::vector<std::unique_ptr<PlayCardAction>> MinionCard::create_play_actions(const Game& game, unsigned hand_position)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned minion_count = game.current_player().hero.board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().hero.mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayMinionAction>(hand_position, mana_cost, board_position));

    return play_self_actions;
}