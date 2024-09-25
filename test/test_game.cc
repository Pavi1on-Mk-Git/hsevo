#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/heroes/GulDan.h"
#include "players/RandomPlayerLogic.h"

TEST_CASE("Initialize game")
{
    Decklist decklist = ogre_deck();
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    for(const auto& player: {game.current_player(), game.opponent()})
    {
        REQUIRE(player.board.minion_count() == 0);
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

    REQUIRE(game.current_player().hand.size() == 3);
    REQUIRE(game.opponent().hand.size() == 5);
}

TEST_CASE("Draw cards")
{
    Decklist deck = ogre_deck();
    std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
    Game game(logic, logic);

    game.draw();

    REQUIRE(game.current_player().hand.size() == 4);

    game.draw(3);

    REQUIRE(game.current_player().hand.size() == 7);
}

TEST_CASE("Fatigue")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({std::make_unique<BoulderfistOgre>(), 4});
    Decklist decklist(std::move(hero), std::move(deck));
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    game.draw(3);

    REQUIRE(game.current_player().hero->health == 27);

    game.draw();

    REQUIRE(game.current_player().hero->health == 24);
}

TEST_CASE("End turn")
{
    Decklist deck = ogre_deck();
    std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
    Game game(logic, logic);

    auto actions = game.get_possible_actions();

    (*(actions.end() - 1))->apply(game);

    REQUIRE(game.turn_ended == true);
}

TEST_CASE("Play cards")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({std::make_unique<BoulderfistOgre>(), 1});
    Decklist decklist(std::move(hero), std::move(deck));
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    game.current_player().mana = 6;

    auto actions = game.get_possible_actions();

    actions.at(0)->apply(game);

    auto& ogre = game.current_player().board.get_minion(0);

    REQUIRE(ogre.active == false);
    REQUIRE(ogre.attack == 6);
    REQUIRE(ogre.health == 7);
    REQUIRE(ogre.keywords == MinionKeywords::NO_KEYWORDS);
    REQUIRE(ogre.max_health == 7);
    REQUIRE(ogre.name == "Boulderfist Ogre");
    REQUIRE(ogre.tribe == Tribe::NONE);
    REQUIRE(ogre.will_die_horribly == false);
}

TEST_CASE("Minion attacks")
{
    Decklist deck = ogre_deck();
    std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
    Game game(logic, logic);

    game.current_player().board.add_minion(Minion(BoulderfistOgre()), 0);
    game.current_player().board.get_minion(0).active = true;
    game.opponent().board.add_minion(Minion(BoulderfistOgre()), 0);

    auto actions = game.get_possible_actions();

    SECTION("Attack hero")
    {
        actions.at(0)->apply(game);

        REQUIRE(game.opponent().hero->health == 24);
    }

    SECTION("Attack minion")
    {
        actions.at(1)->apply(game);

        REQUIRE(game.opponent().board.get_minion(0).health == 1);
        REQUIRE(game.current_player().board.get_minion(0).health == 1);
    }
}