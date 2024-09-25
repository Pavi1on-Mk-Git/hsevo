#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/cards/AncientWatcher.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/cards/Coin.h"
#include "logic/cards/Infernal.h"
#include "logic/cards/LeeroyJenkins.h"
#include "logic/cards/SacrificialPact.h"
#include "logic/heroes/GulDan.h"
#include "logic/heroes/LordJaraxxus.h"
#include "players/RandomPlayerLogic.h"

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

    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().mana == 0);

    auto& ogre = new_state.current_player().board.get_minion(0);

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
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().hero->health == 24);
        REQUIRE(new_state.current_player().board.get_minion(0).active == false);
    }

    SECTION("Attack minion")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 1);
        REQUIRE(new_state.current_player().board.get_minion(0).health == 1);
        REQUIRE(new_state.current_player().board.get_minion(0).active == false);
    }
}

TEST_CASE("Keywords")
{
    SECTION("Can't attack")
    {
        Decklist deck = ogre_deck();
        std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
        Game game(logic, logic);

        game.current_player().board.add_minion(AncientWatcher(), 0);
        game.current_player().board.get_minion(0).active = true;

        REQUIRE(game.get_possible_actions().size() == 1);
    }

    SECTION("Taunt")
    {
        Decklist deck = ogre_deck();
        std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
        Game game(logic, logic);

        game.current_player().board.add_minion(BoulderfistOgre(), 0);
        game.current_player().board.get_minion(0).active = true;

        game.opponent().board.add_minion(BoulderfistOgre(), 0);
        game.opponent().board.add_minion(BoulderfistOgre(), 1);

        REQUIRE(game.get_possible_actions().size() == 4);

        game.opponent().board.get_minion(0).keywords |= TAUNT;

        REQUIRE(game.get_possible_actions().size() == 2);
    }

    SECTION("Charge")
    {
        Decklist deck = ogre_deck();
        std::shared_ptr<PlayerLogic> logic = std::make_shared<RandomPlayerLogic>(deck);
        Game game(logic, logic);

        game.current_player().board.add_minion(LeeroyJenkins(), 0);

        REQUIRE(game.current_player().board.get_minion(0).active == true);
    }
}

TEST_CASE("The Coin")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({std::make_unique<Coin>(), 1});
    Decklist decklist(std::move(hero), std::move(deck));
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    SECTION("Normal use")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(game.current_player().mana == 0);
        auto new_state = actions.at(0)->apply(game);
        REQUIRE(game.current_player().mana == 1);
    }

    SECTION("Full mana use")
    {
        game.current_player().mana = 10;

        auto actions = game.get_possible_actions();
        REQUIRE(game.current_player().mana == 10);
        auto new_state = actions.at(0)->apply(game);
        REQUIRE(game.current_player().mana == 10);
    }
}

TEST_CASE("Sacrificial Pact")
{
    auto hero = std::make_unique<LordJaraxxus>();
    DecklistDeck deck;
    deck.push_back({std::make_unique<SacrificialPact>(), 1});
    Decklist decklist(std::move(hero), std::move(deck));
    auto logic = std::make_shared<RandomPlayerLogic>(decklist);
    Game game(logic, logic);

    game.current_player().board.add_minion(Infernal(), 0);
    game.opponent().board.add_minion(Infernal(), 0);

    auto actions = game.get_possible_actions();

    SECTION("Kill ally demon")
    {
        auto new_state = actions.at(1)->apply(game).at(0);
        REQUIRE(new_state.current_player().board.minion_count() == 0);
    }

    SECTION("Kill enemy demon")
    {
        auto new_state = actions.at(3)->apply(game).at(0);
        REQUIRE(new_state.opponent().board.minion_count() == 0);
    }

    SECTION("Kill yourself")
    {
        auto new_state = actions.at(0)->apply(game).at(0);
        REQUIRE(new_state.current_player().hero->health == 0);
        REQUIRE(new_state.check_winner());
    }

    SECTION("Kill your enemy")
    {
        auto new_state = actions.at(2)->apply(game).at(0);
        REQUIRE(new_state.opponent().hero->health == 0);
        REQUIRE(new_state.check_winner());
    }
}