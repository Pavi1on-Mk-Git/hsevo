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

std::vector<std::unique_ptr<PlayCardAction>> FreezingTrap::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(game.current_player().mana < mana_cost)
        return {};

    if(std::ranges::find(game.current_player().secrets, this) == game.current_player().secrets.end())
        play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, mana_cost));

    return play_self_actions;
}
