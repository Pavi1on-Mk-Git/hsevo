#include "logic/cards/Hellfire.h"

#include "logic/Game.h"

const unsigned HELLFIRE_DMG = 3;

std::vector<Game> Hellfire::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    auto deal_dmg = [&game](Entity& entity) {
        entity.deal_dmg(HELLFIRE_DMG + game.current_player().spell_damage, game);
    };

    auto deal_to_all = [&deal_dmg](Player& player) {
        for(auto& minion: player.board)
            deal_dmg(minion);
    };

    deal_dmg(*game.current_player().hero);
    deal_dmg(*game.opponent().hero);

    deal_to_all(game.current_player());
    deal_to_all(game.opponent());

    return {game};
}
