#include "logic/cards/MinionCard.h"

#include "logic/Game.h"

MinionCard::MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health), keywords(NO_KEYWORDS),
    tribe(Tribe::NONE), has_deathrattle(false)
{}

MinionCard::MinionCard(
    const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const MinionKeywords& keywords
):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health), keywords(keywords), tribe(Tribe::NONE),
    has_deathrattle(false)
{}

MinionCard::MinionCard(
    const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const Tribe& tribe
):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health), keywords(NO_KEYWORDS), tribe(tribe),
    has_deathrattle(false)
{}

MinionCard::MinionCard(
    const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, bool has_deathrattle
):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health), keywords(NO_KEYWORDS),
    tribe(Tribe::NONE), has_deathrattle(has_deathrattle)
{}

MinionCard::MinionCard(
    const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const MinionKeywords& keywords,
    const Tribe& tribe
):
    Card(name, base_cost), base_attack(base_attack), base_health(base_health), keywords(keywords), tribe(tribe),
    has_deathrattle(false)
{}

std::vector<Game> MinionCard::on_death(Game& game, unsigned) const
{
    return {game};
}

void MinionCard::on_minion_summon(Game&, Minion&, unsigned, unsigned) const {}

void MinionCard::on_minion_damaged(Game&, unsigned) const {}

void MinionCard::on_damaged(Game&, unsigned) const {}

void MinionCard::on_summon(Game&, unsigned) const {}

void MinionCard::on_remove(Game&, unsigned, unsigned) const {}

std::vector<Game> MinionCard::on_end_of_turn(Game& game, unsigned, unsigned) const
{
    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> MinionCard::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned minion_count = game.current_player().board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().mana)
        return {};

    for(unsigned board_position = 0; board_position <= minion_count; ++board_position)
        play_self_actions.push_back(std::make_unique<PlayMinionAction>(hand_position, mana_cost, board_position));

    return play_self_actions;
}