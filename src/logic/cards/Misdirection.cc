#include "logic/cards/Misdirection.h"

#include "logic/Game.h"

std::vector<Game> Misdirection::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().secrets.push_back(this);
    return {game};
}

SecretResult Misdirection::on_trigger(Game& game, const FightAction& action) const
{
    using enum TargetType;

    std::vector<FightAction> actions;

    switch(action.attacker)
    {
    case ALLY_MINION:
        switch(action.defender)
        {
        case ENEMY_MINION:
            for(unsigned minion_position = 0; minion_position < game.current_player().board.minion_count();
                ++minion_position)
                if(minion_position != action.attacker_position)
                    actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < game.opponent().board.minion_count(); ++minion_position)
                if(minion_position != action.defender_position)
                    actions.emplace_back(ALLY_MINION, *action.attacker_position, ENEMY_MINION, minion_position);

            actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_HERO);
            actions.emplace_back(ALLY_MINION, *action.attacker_position, ENEMY_HERO);
            break;
        case ENEMY_HERO:
            for(unsigned minion_position = 0; minion_position < game.current_player().board.minion_count();
                ++minion_position)
                if(minion_position != action.attacker_position)
                    actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < game.opponent().board.minion_count(); ++minion_position)
                actions.emplace_back(ALLY_MINION, *action.attacker_position, ENEMY_MINION, minion_position);

            actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_HERO);
            break;
        default:
            break;
        }
        break;
    case ALLY_HERO:
        switch(action.defender)
        {
        case ENEMY_MINION:
            for(unsigned minion_position = 0; minion_position < game.current_player().board.minion_count();
                ++minion_position)
                actions.emplace_back(ALLY_HERO, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < game.opponent().board.minion_count(); ++minion_position)
                if(minion_position != action.defender_position)
                    actions.emplace_back(ALLY_HERO, ENEMY_MINION, minion_position);

            actions.emplace_back(ALLY_HERO, ENEMY_HERO);
            break;
        case ENEMY_HERO:
            for(unsigned minion_position = 0; minion_position < game.current_player().board.minion_count();
                ++minion_position)
                actions.emplace_back(ALLY_HERO, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < game.opponent().board.minion_count(); ++minion_position)
                actions.emplace_back(ALLY_HERO, ENEMY_MINION, minion_position);
            break;
        default:
            break;
        }
        break;
    default:
        return SecretResult();
    }

    std::vector<Game> states;
    for(unsigned i = 0; i < actions.size(); ++i)
        states.push_back(game);

    return SecretResult(states, actions, true);
}

std::vector<std::unique_ptr<PlayCardAction>> Misdirection::create_play_actions(const Game& game, unsigned hand_position)
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
