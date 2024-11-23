#include "logic/cards/Whirlwind.h"

#include "logic/Game.h"

const unsigned WHIRLWIND_DMG = 1;

std::vector<Game> Whirlwind::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    auto deal_to_all = [&game](Player& player) {
        for(auto& minion: player.board)
            minion.deal_dmg(WHIRLWIND_DMG + game.current_player().spell_damage, game);
    };

    deal_to_all(game.current_player());
    deal_to_all(game.opponent());

    return {game};
}
