#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/decklists.h"
#include "players/RandomPlayerLogic.h"

TEST_CASE("Gul'Dan")
{
    Decklist decklist = handlock();
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    (*(actions.end() - 2))->apply(game);

    REQUIRE(game.current_player().hero->health == 28);
    REQUIRE(game.current_player().hand.size() == 4);
}