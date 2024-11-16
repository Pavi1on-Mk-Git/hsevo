#include "logic/cards/ExplosiveTrap.h"

#include "logic/Game.h"

std::vector<Game> ExplosiveTrap::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().secrets.push_back(this);
    return {game};
}

SecretResult ExplosiveTrap::on_trigger(Game& game, const FightAction& action) const
{
    using enum TargetType;

    switch(action.defender)
    {
    case ENEMY_HERO: {
        auto& player = game.current_player();

        for(auto& minion: player.board)
            minion.health -= 2;

        player.hero->health -= 2;

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