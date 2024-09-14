#include "logic/run_game.h"

#include "utils/Rng.h"

GameResult run_game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player)
{
    Game game(first_player, second_player);

    game.active_player_ = Rng::instance()->uniform_int(0, 1);

    game.mulligan();
    while(!game.game_ended_)
        do_turn(game);

    return game.winner_;
}

void do_turn(Game& game)
{
    game.draw();

    game.check_winner();
    if(game.game_ended_)
        return;

    game.current_player().mana = ++game.current_player().mana_crystals;
    game.current_player().hero->hero_power_active = true;

    for(unsigned minion_index = 0; minion_index < game.current_player().board.minion_count(); ++minion_index)
        game.current_player().board.get_minion(minion_index).active = true;

    game.turn_ended_ = false;

    while(!game.turn_ended_)
    {
        game = game.current_player().logic->choose_and_apply_action(game, game.get_possible_actions());

        game.check_winner();
        if(game.game_ended_)
            return;
    }

    game.switch_active_player();
}
