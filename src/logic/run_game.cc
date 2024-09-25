#include "logic/run_game.h"

#include "utils/Rng.h"

std::optional<GameResult> do_turn(Game& game)
{
    std::optional<GameResult> winner = std::nullopt;

    game.draw();

    if((winner = game.check_winner()))
        return winner;

    auto& current_mana_crystals = game.current_player().mana_crystals;

    if(current_mana_crystals < Player::MAX_MANA)
        current_mana_crystals++;

    game.current_player().mana = current_mana_crystals;
    game.current_player().hero->hero_power_active = true;
    game.current_player().hero->active = true;

    for(unsigned minion_index = 0; minion_index < game.current_player().board.minion_count(); ++minion_index)
        game.current_player().board.get_minion(minion_index).active = true;

    game.turn_ended = false;

    while(!game.turn_ended)
    {
        game = game.current_player().logic->choose_and_apply_action(game, game.get_possible_actions());

        if((winner = game.check_winner()))
            return winner;
    }

    return std::nullopt;
}

GameResult run_game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player)
{
    Game game(first_player, second_player);

    std::optional<GameResult> winner = game.check_winner();

    while(!winner)
    {
        winner = do_turn(game);
        game.switch_active_player();
    }

    return *winner;
}
