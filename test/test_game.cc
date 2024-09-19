#include <catch2/catch_test_macros.hpp>

#include "logic/run_game.h"
#include "players/RandomPlayerLogic.h"

TEST_CASE("Initialize game")
{
    Decklist deck = ogre_deck();
    std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
    Game game(logic, logic);

    SECTION("Check initial state")
    {
        for(const auto& player: {game.current_player(), game.opponent()})
        {
            REQUIRE(player.board.minion_count() == 0);
            REQUIRE(player.hand.size() == 0);
            REQUIRE(player.hero->active == true);
            REQUIRE(player.hero->health == 30);
            REQUIRE(player.hero->max_health == 30);
            REQUIRE(player.hero->hero_power_active == true);
            REQUIRE(player.hero->hero_power_mana_cost == 2);
            REQUIRE(player.hero->hero_power_name == "Life Tap");
            REQUIRE(player.hero->name == "Gul'Dan");
            REQUIRE(player.hero->tribe == Tribe::NONE);
            REQUIRE_FALSE(player.hero->weapon.has_value());
            REQUIRE(player.mana == 0);
            REQUIRE(player.mana_crystals == 0);
        }
    }
}