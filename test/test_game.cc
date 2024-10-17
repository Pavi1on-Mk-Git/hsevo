#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/heroes/GulDan.h"

TEST_CASE("Initialize game")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist);

    for(const auto& player: {game.current_player(), game.opponent()})
    {
        REQUIRE(player.board.minion_count() == 0);
        REQUIRE(player.hero->active);
        REQUIRE(player.hero->health == 30);
        REQUIRE(player.hero->max_health == 30);
        REQUIRE(player.hero->hero_power_active);
        REQUIRE(player.hero->hero_power_mana_cost == 2);
        REQUIRE(std::strcmp(player.hero->hero_power_name, "Life Tap") == 0);
        REQUIRE(std::strcmp(player.hero->name, "Gul'Dan") == 0);
        REQUIRE(player.hero->tribe == Tribe::NONE);
        REQUIRE_FALSE(player.hero->weapon.has_value());
        REQUIRE(player.mana == 0);
        REQUIRE(player.mana_crystals == 0);
    }

    REQUIRE(game.current_player().hand.size() == 3);
    REQUIRE(game.opponent().hand.size() == 5);
}

TEST_CASE("Draw cards")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist);

    game.draw();

    REQUIRE(game.current_player().hand.size() == 4);

    game.draw(3);

    REQUIRE(game.current_player().hand.size() == 7);
}

TEST_CASE("Fatigue")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&BoulderfistOgre::instance, 4});
    Decklist decklist(std::move(hero), std::move(deck));
    Game game(decklist, decklist);

    game.draw(3);

    REQUIRE(game.current_player().hero->health == 27);

    game.draw();

    REQUIRE(game.current_player().hero->health == 24);
}

TEST_CASE("End turn")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist);

    auto actions = game.get_possible_actions();

    auto new_state = (*(actions.end() - 1))->apply(game).at(0);

    REQUIRE(new_state.turn_ended);
}

TEST_CASE("Tie")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist);

    game.current_player().hero->health = 0;
    game.opponent().hero->health = 0;

    REQUIRE(*game.check_winner() == GameResult::TIE);
}

TEST_CASE("Game unfinished")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist);

    REQUIRE_FALSE(game.check_winner());
}
