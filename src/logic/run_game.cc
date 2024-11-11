#include "logic/run_game.h"

#include <spdlog/spdlog.h>

#include "utils/Rng.h"

std::optional<GameResult> do_turn(Game& game, const std::unique_ptr<PlayerLogic>& logic)
{
    std::optional<GameResult> winner;

    game.draw();

    if((winner = game.check_winner()))
        return winner;

    auto& current_mana_crystals = game.current_player().mana_crystals;

    if(current_mana_crystals < Player::MAX_MANA)
        current_mana_crystals++;

    game.current_player().mana = current_mana_crystals;
    game.current_player().hero->hero_power_active = true;
    game.current_player().hero->active = true;

    for(auto& minion: game.current_player().board)
        minion.active = true;

    game.turn_ended = false;

    while(!game.turn_ended)
    {
        game = logic->choose_and_apply_action(game, game.get_possible_actions());

        if((winner = game.check_winner()))
            return winner;
    }

    return std::nullopt;
}

GameResult run_game(const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player)
{
    Game game(first_player->decklist, second_player->decklist);

    std::optional<GameResult> winner = game.check_winner();

    unsigned global_turn = 0;

    while(!winner)
    {
        ++global_turn;
        SPDLOG_INFO(
            "Turn number {} of the {} player has begun.", (global_turn + 1) / 2,
            (global_turn % 2) == 1 ? "first" : "second"
        );
        winner = do_turn(game, (global_turn % 2) == 1 ? first_player : second_player);
        game.switch_active_player();
    }

    return *winner;
}
