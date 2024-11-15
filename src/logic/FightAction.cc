#include "logic/FightAction.h"

#include "logic/Game.h"

FightAction::FightAction(
    const TargetType& attacker, unsigned attacker_position, const TargetType& defender, unsigned defender_position
): attacker(attacker), defender(defender), attacker_position(attacker_position), defender_position(defender_position)
{}

FightAction::FightAction(const TargetType& attacker, const TargetType& defender, unsigned defender_position):
    attacker(attacker), defender(defender), defender_position(defender_position)
{}

FightAction::FightAction(const TargetType& attacker, unsigned attacker_position, const TargetType& defender):
    attacker(attacker), defender(defender), attacker_position(attacker_position)
{}

FightAction::FightAction(const TargetType& attacker, const TargetType& defender): attacker(attacker), defender(defender)
{}

std::vector<Game> FightAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> FightAction::element_sequence() const
{
    using enum GuiElementIdType;
    using enum TargetType;
    std::deque<GuiElementId> sequence;

    switch(attacker)
    {
    case ALLY_MINION:
        sequence.push_back(std::make_tuple(MINION, true, *attacker_position));
        break;
    case ALLY_HERO:
        sequence.push_back(std::make_pair(HERO, true));
        break;
    default:
        break;
    }

    switch(defender)
    {
    case ENEMY_MINION:
        sequence.push_back(std::make_tuple(MINION, false, *defender_position));
        break;
    case ENEMY_HERO:
        sequence.push_back(std::make_pair(HERO, false));
        break;
    default:
        break;
    }

    return sequence;
}