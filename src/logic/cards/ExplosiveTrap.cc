#include "logic/cards/ExplosiveTrap.h"

#include "logic/Game.h"

std::vector<Game> ExplosiveTrap::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().secrets.push_back(this);
    return {game};
}

const unsigned EXPLOSIVE_TRAP_DMG = 2;

SecretResult ExplosiveTrap::on_trigger(Game& game, const FightAction& action) const
{
    using enum TargetType;

    switch(action.defender)
    {
    case ENEMY_HERO: {
        auto& player = game.current_player();

        const unsigned spell_dmg = game.opponent().spell_damage;

        for(auto& minion: player.board)
            minion.deal_dmg(EXPLOSIVE_TRAP_DMG + spell_dmg, game);

        player.hero->deal_dmg(EXPLOSIVE_TRAP_DMG + spell_dmg, game);

        bool can_continue;
        switch(action.attacker)
        {
        case ALLY_MINION:
            can_continue = player.board.get_minion(*action.attacker_position).health > 0;
            break;
        case ALLY_HERO:
            can_continue = player.hero->health > 0;
            break;
        default:
            return SecretResult();
        }

        return SecretResult({game}, {action}, can_continue);
    }
    default:
        return SecretResult();
    }
}

std::vector<std::unique_ptr<PlayCardAction>> ExplosiveTrap::create_play_actions(
    const Game& game, unsigned hand_position
) const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(game.current_player().mana < mana_cost)
        return {};

    if(std::ranges::find(game.current_player().secrets, this) == game.current_player().secrets.end())
        play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, mana_cost));

    return play_self_actions;
}
