#include "logic/cards/Whirlwind.h"

#include "logic/Game.h"

const unsigned WHIRLWIND_DMG = 1;

std::vector<Game> Whirlwind::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    auto deal_to_all = [&game](Player& player) {
        for(auto& minion: player.board)
            minion.deal_dmg(WHIRLWIND_DMG + game.current_player().spell_damage, game);
    };

    deal_to_all(game.current_player());
    deal_to_all(game.opponent());

    return resulting_states;
}
