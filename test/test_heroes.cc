#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/decklists.h"

TEST_CASE("Gul'Dan")
{
    Decklist decklist = handlock();
    Game game(decklist, decklist);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 2))->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->health == 28);
    REQUIRE(new_state.current_player().hand.size() == 4);
}

TEST_CASE("Rexxar")
{
    Decklist decklist = face_hunter();
    Game game(decklist, decklist);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 2))->apply(game).at(0);

    REQUIRE(new_state.opponent().hero->health == 28);
}