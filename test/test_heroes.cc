#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/decklists.h"

static Rng rng(42);

TEST_CASE("Gul'Dan")
{
    Decklist decklist = handlock();
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 2))->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->health == 28);
    REQUIRE(new_state.current_player().hand.size() == 4);
}

TEST_CASE("Rexxar")
{
    Decklist decklist = face_hunter();
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 2))->apply(game).at(0);

    REQUIRE(new_state.opponent().hero->health == 28);
}

TEST_CASE("Garrosh Hellscream")
{
    Decklist decklist = control_warrior();
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 2))->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->armour == 2);
}
