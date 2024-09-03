#include "logic/cards/Hellfire.h"

#include "logic/Game.h"

const unsigned HELLFIRE_DMG = 3;

std::vector<Game> Hellfire::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    auto deal_dmg = [](Entity& entity) { entity.health -= HELLFIRE_DMG; };

    auto deal_to_all = [&deal_dmg](Hero& hero) {
        deal_dmg(hero);
        for(unsigned target_position = 0; target_position < hero.board.minion_count(); ++target_position)
            deal_dmg(hero.board.get_minion(target_position));
    };

    deal_to_all(game.current_player().hero);
    deal_to_all(game.opponent().hero);

    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> Hellfire::create_play_actions(const Game& game, unsigned hand_position)
{
    return {
        std::make_unique<PlayCardAction>(
            hand_position, game.current_player().hero.hand.get_card(hand_position)->mana_cost(game)
        ),
    };
}