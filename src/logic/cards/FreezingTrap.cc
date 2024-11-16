#include "logic/cards/FreezingTrap.h"

#include "logic/Game.h"

std::vector<Game> FreezingTrap::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().secrets.push_back(this);
    return {game};
}

static const unsigned FREEZING_TRAP_COST_INCREASE = 2;

SecretResult FreezingTrap::on_trigger(Game& game, const FightAction& action) const
{
    using enum TargetType;

    switch(action.attacker)
    {
    case ALLY_MINION:
        switch(action.defender)
        {
        case ENEMY_MINION:
        case ENEMY_HERO: {
            const auto* bounced_minion = game.bounce_minion(*action.attacker_position);
            auto card_with_cost_increase = HandCard(bounced_minion, FREEZING_TRAP_COST_INCREASE);
            game.current_player().hand.add_cards(card_with_cost_increase);
            return SecretResult({game}, {action}, false);
        }
        default:
            break;
        }
    default:
        break;
    }
    return SecretResult();
}