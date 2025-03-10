#include <catch2/catch_test_macros.hpp>

#include "logic/Game.h"
#include "logic/cards/AbusiveSergeant.h"
#include "logic/cards/AcolyteOfPain.h"
#include "logic/cards/Alexstraza.h"
#include "logic/cards/AncientWatcher.h"
#include "logic/cards/ArcaneGolem.h"
#include "logic/cards/Armorsmith.h"
#include "logic/cards/AzureDrake.h"
#include "logic/cards/BaronGeddon.h"
#include "logic/cards/BigGameHunter.h"
#include "logic/cards/BloodFury.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/cards/Brawl.h"
#include "logic/cards/CairneBloodhoof.h"
#include "logic/cards/Coin.h"
#include "logic/cards/CruelTaskmaster.h"
#include "logic/cards/DefenderOfArgus.h"
#include "logic/cards/EaglehornBow.h"
#include "logic/cards/EarthenRingFarseer.h"
#include "logic/cards/Execute.h"
#include "logic/cards/ExplosiveTrap.h"
#include "logic/cards/FacelessManipulator.h"
#include "logic/cards/Flare.h"
#include "logic/cards/FreezingTrap.h"
#include "logic/cards/GrommashHellscream.h"
#include "logic/cards/Hellfire.h"
#include "logic/cards/HuntersMark.h"
#include "logic/cards/Infernal.h"
#include "logic/cards/KillCommand.h"
#include "logic/cards/LeeroyJenkins.h"
#include "logic/cards/LeperGnome.h"
#include "logic/cards/LordJaraxxusCard.h"
#include "logic/cards/Misdirection.h"
#include "logic/cards/MoltenGiant.h"
#include "logic/cards/MortalCoil.h"
#include "logic/cards/MountainGiant.h"
#include "logic/cards/PowerOverwhelming.h"
#include "logic/cards/RagnarosTheFirelord.h"
#include "logic/cards/SacrificialPact.h"
#include "logic/cards/Shadowflame.h"
#include "logic/cards/ShieldBlock.h"
#include "logic/cards/ShieldSlam.h"
#include "logic/cards/SiphonSoul.h"
#include "logic/cards/Slam.h"
#include "logic/cards/Soulfire.h"
#include "logic/cards/StarvingBuzzard.h"
#include "logic/cards/SunfuryProtector.h"
#include "logic/cards/SylvanasWindrunner.h"
#include "logic/cards/TimberWolf.h"
#include "logic/cards/Tracking.h"
#include "logic/cards/TwilightDrake.h"
#include "logic/cards/UnleashTheHounds.h"
#include "logic/cards/Whirlwind.h"
#include "logic/decklists.h"
#include "logic/heroes/GarroshHellscream.h"
#include "logic/heroes/GulDan.h"
#include "logic/heroes/LordJaraxxus.h"
#include "logic/heroes/Rexxar.h"

static Rng rng(42);

TEST_CASE("Play cards")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&BoulderfistOgre::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 6;

    auto actions = game.get_possible_actions();

    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().mana == 0);

    auto& ogre = new_state.current_player().board.get_minion(0);

    REQUIRE_FALSE(ogre.active);
    REQUIRE(ogre.attack == 6);
    REQUIRE(ogre.health == 7);
    REQUIRE(ogre.keywords == MinionKeywords::NO_KEYWORDS);
    REQUIRE(ogre.max_health == 7);
    REQUIRE(std::strcmp(ogre.name, "Boulderfist Ogre") == 0);
    REQUIRE(ogre.tribe == Tribe::NONE);
    REQUIRE_FALSE(ogre.will_die_horribly);
}

TEST_CASE("Minion attacks")
{
    Decklist decklist = ogre_deck();
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.current_player().board.get_minion(0).active = true;
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    auto actions = game.get_possible_actions();

    SECTION("Attack hero")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().hero->health == 24);
        REQUIRE_FALSE(new_state.current_player().board.get_minion(0).active);
    }

    SECTION("Attack minion")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 1);
        REQUIRE(new_state.current_player().board.get_minion(0).health == 1);
        REQUIRE_FALSE(new_state.current_player().board.get_minion(0).active);
    }
}

TEST_CASE("Keywords")
{
    SECTION("Can't attack")
    {
        Decklist decklist = ogre_deck();
        Game game(decklist, decklist, rng);

        game.add_minion(&AncientWatcher::instance, 0);
        game.current_player().board.get_minion(0).active = true;

        REQUIRE(game.get_possible_actions().size() == 1);
    }

    SECTION("Taunt")
    {
        Decklist decklist = ogre_deck();
        Game game(decklist, decklist, rng);

        game.add_minion(&BoulderfistOgre::instance, 0);
        game.current_player().board.get_minion(0).active = true;

        game.add_minion(&BoulderfistOgre::instance, 0, false);
        game.add_minion(&BoulderfistOgre::instance, 1, false);

        REQUIRE(game.get_possible_actions().size() == 4);

        game.opponent().board.get_minion(0).keywords |= TAUNT;

        REQUIRE(game.get_possible_actions().size() == 2);
    }

    SECTION("Charge")
    {
        Decklist decklist = ogre_deck();
        Game game(decklist, decklist, rng);

        game.add_minion(&LeeroyJenkins::instance, 0);

        REQUIRE(game.current_player().board.get_minion(0).active);
    }
}

TEST_CASE("Secrets")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&ExplosiveTrap::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().secrets.size() == 1);

    new_state.current_player().mana = 2;

    REQUIRE(new_state.get_possible_actions().size() == 2);

    new_state.switch_active_player();

    new_state.add_minion(&BoulderfistOgre::instance, 0);
    new_state.current_player().board.get_minion(0).active = true;

    auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

    REQUIRE(post_attack_state.opponent().secrets.empty());
}

TEST_CASE("Weapons")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&BloodFury::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    SECTION("Attack hero and destroy weapon")
    {
        new_state.current_player().hero->weapon->durability = 1;

        auto actions = new_state.get_possible_actions();
        auto post_attack_state = actions.at(0)->apply(new_state).at(0);

        REQUIRE_FALSE(post_attack_state.current_player().hero->active);
        REQUIRE_FALSE(post_attack_state.current_player().hero->weapon);
        REQUIRE(post_attack_state.opponent().hero->health == 27);
    }

    SECTION("Attack taunt minion and destroy weapon")
    {
        new_state.current_player().hero->weapon->durability = 1;
        new_state.add_minion(&BoulderfistOgre::instance, 0, false);
        new_state.opponent().board.get_minion(0).keywords |= TAUNT;

        auto actions = new_state.get_possible_actions();
        auto post_attack_state = actions.at(0)->apply(new_state).at(0);

        REQUIRE_FALSE(post_attack_state.current_player().hero->active);
        REQUIRE_FALSE(post_attack_state.current_player().hero->weapon);
        REQUIRE(post_attack_state.current_player().hero->health == 24);
        REQUIRE(post_attack_state.opponent().board.get_minion(0).health == 4);
    }
}

TEST_CASE("The Coin")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&Coin::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    SECTION("Normal use")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(game.current_player().mana == 0);
        auto new_state = actions.at(0)->apply(game).at(0);
        REQUIRE(new_state.current_player().mana == 1);
    }

    SECTION("Full mana use")
    {
        game.current_player().mana = 10;

        auto actions = game.get_possible_actions();
        REQUIRE(game.current_player().mana == 10);
        auto new_state = actions.at(0)->apply(game).at(0);
        REQUIRE(new_state.current_player().mana == 10);
    }
}

TEST_CASE("Sacrificial Pact")
{
    auto hero = std::make_unique<LordJaraxxus>();
    DecklistDeck deck;
    deck.push_back({&SacrificialPact::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&Infernal::instance, 0);
    game.add_minion(&Infernal::instance, 0, false);

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

TEST_CASE("Soulfire")
{
    SECTION("Regular use")
    {
        auto hero = std::make_unique<GulDan>();
        DecklistDeck deck;
        deck.push_back({&Soulfire::instance, 1});
        deck.push_back({&BoulderfistOgre::instance, 5});
        Decklist decklist("Test", std::move(hero), std::move(deck));
        Game game(decklist, decklist, rng);

        game.draw(3);
        game.add_minion(&BoulderfistOgre::instance, 0);
        game.add_minion(&BoulderfistOgre::instance, 0, false);

        auto actions = game.get_possible_actions();

        SECTION("Target ally hero")
        {
            auto new_states = actions.at(0)->apply(game);
            REQUIRE(new_states.size() == 5);
            for(const auto& state: new_states)
            {
                REQUIRE(state.current_player().hero->health == 26);
                REQUIRE(state.current_player().hand.size() == 4);
            }
        }

        SECTION("Target enemy hero")
        {
            auto new_states = actions.at(2)->apply(game);
            REQUIRE(new_states.size() == 5);
            for(const auto& state: new_states)
            {
                REQUIRE(state.opponent().hero->health == 26);
                REQUIRE(state.current_player().hand.size() == 4);
            }
        }

        SECTION("Target ally minion")
        {
            auto new_states = actions.at(1)->apply(game);
            REQUIRE(new_states.size() == 5);
            for(const auto& state: new_states)
            {
                REQUIRE(state.current_player().board.get_minion(0).health == 3);
                REQUIRE(state.current_player().hand.size() == 4);
            }
        }

        SECTION("Target enemy hero")
        {
            auto new_states = actions.at(3)->apply(game);
            REQUIRE(new_states.size() == 5);
            for(const auto& state: new_states)
            {
                REQUIRE(state.opponent().board.get_minion(0).health == 3);
                REQUIRE(state.current_player().hand.size() == 4);
            }
        }
    }

    SECTION("Empty hand")
    {
        auto hero = std::make_unique<GulDan>();
        DecklistDeck deck;
        deck.push_back({&Soulfire::instance, 1});
        Decklist decklist("Test", std::move(hero), std::move(deck));
        Game game(decklist, decklist, rng);

        auto actions = game.get_possible_actions();

        REQUIRE(actions.at(0)->apply(game).size() == 1);
    }
}

TEST_CASE("Mortal Coil")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&MortalCoil::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 1;

    SECTION("Target ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).health == 6);
        REQUIRE(new_state.current_player().hand.size() == 2);
    }

    SECTION("Draw card from ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);
        game.current_player().board.get_minion(0).health = 1;

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hand.size() == 3);
    }

    SECTION("Target enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 6);
        REQUIRE(new_state.current_player().hand.size() == 2);
    }

    SECTION("Draw card from enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);
        game.opponent().board.get_minion(0).health = 1;

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hand.size() == 3);
    }
}

TEST_CASE("Power Overwhelming")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&PowerOverwhelming::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.current_player().mana = 1;

    auto actions = game.get_possible_actions();
    auto new_state = actions.at(0)->apply(game).at(0);

    auto& ogre = new_state.current_player().board.get_minion(0);

    REQUIRE(ogre.attack == 10);
    REQUIRE(ogre.max_health == 11);
    REQUIRE(ogre.health == 11);
    REQUIRE(ogre.will_die_horribly);

    actions = new_state.get_possible_actions();
    auto next_state = (*(actions.end() - 1))->apply(new_state).at(0);

    REQUIRE(next_state.current_player().board.minion_count() == 0);
}

TEST_CASE("Sunfury Protector")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&SunfuryProtector::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);
    game.current_player().mana = 2;


    auto actions = game.get_possible_actions();

    SECTION("Played left")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(1).keywords == TAUNT);
        REQUIRE(new_state.current_player().board.get_minion(2).keywords == NO_KEYWORDS);
    }

    SECTION("Played middle")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).keywords == TAUNT);
        REQUIRE(new_state.current_player().board.get_minion(2).keywords == TAUNT);
    }

    SECTION("Played right")
    {
        auto new_state = actions.at(2)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(1).keywords == TAUNT);
        REQUIRE(new_state.current_player().board.get_minion(0).keywords == NO_KEYWORDS);
    }
}

TEST_CASE("Earthen Ring Farseer")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&EarthenRingFarseer::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.current_player().board.get_minion(0).health -= 2;

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.opponent().board.get_minion(0).health -= 4;

    auto actions = game.get_possible_actions();

    SECTION("Heal yourself")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().hero->health == 30);
    }

    SECTION("Heal enemy")
    {
        auto new_state = actions.at(2)->apply(game).at(0);

        REQUIRE(new_state.opponent().hero->health == 27);
    }

    SECTION("Heal ally minion")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(1).health == 7);
    }

    SECTION("Heal enemy minion")
    {
        auto new_state = actions.at(3)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 6);
    }
}

TEST_CASE("Defender of Argus")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&DefenderOfArgus::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);
    game.current_player().mana = 4;


    auto actions = game.get_possible_actions();

    SECTION("Played left")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        auto& first_minion = new_state.current_player().board.get_minion(1);
        auto& second_minion = new_state.current_player().board.get_minion(2);

        REQUIRE(first_minion.keywords == TAUNT);
        REQUIRE(first_minion.attack == 7);
        REQUIRE(first_minion.max_health == 8);
        REQUIRE(first_minion.health == 8);
        REQUIRE(second_minion.keywords == NO_KEYWORDS);
        REQUIRE(second_minion.attack == 6);
        REQUIRE(second_minion.max_health == 7);
        REQUIRE(second_minion.health == 7);
    }

    SECTION("Played middle")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        auto& first_minion = new_state.current_player().board.get_minion(0);
        auto& second_minion = new_state.current_player().board.get_minion(2);

        REQUIRE(first_minion.keywords == TAUNT);
        REQUIRE(first_minion.attack == 7);
        REQUIRE(first_minion.max_health == 8);
        REQUIRE(first_minion.health == 8);
        REQUIRE(second_minion.keywords == TAUNT);
        REQUIRE(second_minion.attack == 7);
        REQUIRE(second_minion.max_health == 8);
        REQUIRE(second_minion.health == 8);
    }

    SECTION("Played right")
    {
        auto new_state = actions.at(2)->apply(game).at(0);

        auto& first_minion = new_state.current_player().board.get_minion(1);
        auto& second_minion = new_state.current_player().board.get_minion(0);

        REQUIRE(first_minion.keywords == TAUNT);
        REQUIRE(first_minion.attack == 7);
        REQUIRE(first_minion.max_health == 8);
        REQUIRE(first_minion.health == 8);
        REQUIRE(second_minion.keywords == NO_KEYWORDS);
        REQUIRE(second_minion.attack == 6);
        REQUIRE(second_minion.max_health == 7);
        REQUIRE(second_minion.health == 7);
    }
}

TEST_CASE("Hellfire")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&Hellfire::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 4;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto actions = game.get_possible_actions();

    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->health == 27);
    REQUIRE(new_state.opponent().hero->health == 27);
    REQUIRE(new_state.current_player().board.get_minion(0).health == 4);
    REQUIRE(new_state.current_player().board.get_minion(1).health == 4);
    REQUIRE(new_state.opponent().board.get_minion(0).health == 4);
    REQUIRE(new_state.opponent().board.get_minion(1).health == 4);
}

TEST_CASE("Leeroy Jenkins")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&LeeroyJenkins::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 5;

    auto actions = game.get_possible_actions();
    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.opponent().board.minion_count() == 2);
}

TEST_CASE("Shadowflame")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&Shadowflame::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 4;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto actions = game.get_possible_actions();
    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().board.minion_count() == 0);
    REQUIRE(new_state.opponent().board.get_minion(0).health == 1);
    REQUIRE(new_state.opponent().board.get_minion(1).health == 1);
}

TEST_CASE("Twilight Drake")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&TwilightDrake::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 4;

    SECTION("3 card hand")
    {
        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).max_health == 3);
        REQUIRE(new_state.current_player().board.get_minion(0).health == 3);
    }

    SECTION("5 card hand")
    {
        game.draw(2);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).max_health == 5);
        REQUIRE(new_state.current_player().board.get_minion(0).health == 5);
    }
}

TEST_CASE("Faceless Manipulator")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&FacelessManipulator::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 5;

    SECTION("No target")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(actions.size() == 3);
    }

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.current_player().board.get_minion(0).active = true;

    auto actions = game.get_possible_actions();
    auto new_state = actions.at(0)->apply(game).at(0);

    auto& faceless = new_state.current_player().board.get_minion(0);

    REQUIRE_FALSE(faceless.active); // Faceless manipulator can't attack even if the minion can
    REQUIRE(faceless.attack == 6);
    REQUIRE(faceless.health == 7);
    REQUIRE(faceless.keywords == MinionKeywords::NO_KEYWORDS);
    REQUIRE(faceless.max_health == 7);
    REQUIRE(std::strcmp(faceless.name, "Boulderfist Ogre") == 0);
    REQUIRE(faceless.tribe == Tribe::NONE);
    REQUIRE_FALSE(faceless.will_die_horribly);

    auto& ogre = new_state.current_player().board.get_minion(1);

    REQUIRE(ogre.active);
    REQUIRE(ogre.attack == 6);
    REQUIRE(ogre.health == 7);
    REQUIRE(ogre.keywords == MinionKeywords::NO_KEYWORDS);
    REQUIRE(ogre.max_health == 7);
    REQUIRE(std::strcmp(ogre.name, "Boulderfist Ogre") == 0);
    REQUIRE(ogre.tribe == Tribe::NONE);
    REQUIRE_FALSE(ogre.will_die_horribly);
}

TEST_CASE("Siphon Soul")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&SiphonSoul::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 6;

    SECTION("Target ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hero->health == 30);
    }

    SECTION("Target enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hero->health == 30);
    }
}

TEST_CASE("Mountain Giant")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&MountainGiant::instance, 1});
    deck.push_back({&BoulderfistOgre::instance, 8});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 4;

    REQUIRE(game.get_possible_actions().size() == 2);

    game.draw(6);

    REQUIRE(game.get_possible_actions().size() == 3);
}

TEST_CASE("Molten Giant")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&MoltenGiant::instance, 1});
    deck.push_back({&BoulderfistOgre::instance, 2});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    REQUIRE(game.get_possible_actions().size() == 1);

    game.current_player().hero->health -= 20;

    REQUIRE(game.get_possible_actions().size() == 2);
}

TEST_CASE("Lord Jaraxxus")
{
    auto hero = std::make_unique<GulDan>();
    DecklistDeck deck;
    deck.push_back({&LordJaraxxusCard::instance, 4});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 9;
    game.current_player().hero->active = false;

    auto actions = game.get_possible_actions();
    auto new_state = actions.at(0)->apply(game).at(0);

    auto& jaraxxus = new_state.current_player().hero;

    REQUIRE_FALSE(jaraxxus->active); // Changing hero doesn't reset the active state
    REQUIRE(jaraxxus->max_health == 15);
    REQUIRE(jaraxxus->health == 15);
    REQUIRE(jaraxxus->hero_power_active);
    REQUIRE(jaraxxus->hero_power_mana_cost == 2);
    REQUIRE(std::strcmp(jaraxxus->hero_power_name, "INFERNO!") == 0);
    REQUIRE(std::strcmp(jaraxxus->name, "Lord Jaraxxus") == 0);
    REQUIRE(jaraxxus->tribe == Tribe::DEMON);
    REQUIRE(jaraxxus->weapon->attack == 3);
    REQUIRE(jaraxxus->weapon->durability == 8);

    jaraxxus->active = true;

    SECTION("Hero power")
    {
        new_state.current_player().mana = 2;

        auto actions = new_state.get_possible_actions();
        auto post_hero_power_state = actions.at(1)->apply(new_state).at(0);

        auto& infernal = post_hero_power_state.current_player().board.get_minion(0);

        REQUIRE_FALSE(infernal.active);
        REQUIRE(infernal.attack == 6);
        REQUIRE(infernal.health == 6);
        REQUIRE(infernal.keywords == MinionKeywords::NO_KEYWORDS);
        REQUIRE(infernal.max_health == 6);
        REQUIRE(std::strcmp(infernal.name, "Infernal") == 0);
        REQUIRE(infernal.tribe == Tribe::DEMON);
        REQUIRE_FALSE(infernal.will_die_horribly);
    }
}

TEST_CASE("Hunter's Mark")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&HuntersMark::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    SECTION("Target ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).health == 1);
        REQUIRE(new_state.current_player().board.get_minion(0).max_health == 1);
    }

    SECTION("Target enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 1);
        REQUIRE(new_state.opponent().board.get_minion(0).max_health == 1);
    }
}

TEST_CASE("Abusive Sergeant")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&AbusiveSergeant::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 1;

    SECTION("No target")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(actions.size() == 2);
    }

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    auto actions = game.get_possible_actions();

    SECTION("Buff ally minion")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(1).attack == 8);
    }

    SECTION("Buff enemy minion")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).attack == 8);
    }
}

TEST_CASE("Leper Gnome")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&SiphonSoul::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 6;
    game.add_minion(&LeperGnome::instance, 0, false);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->health == 28);
}

TEST_CASE("Timber Wolf")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&TimberWolf::instance, 1});
    deck.push_back({&StarvingBuzzard::instance, 1});
    deck.push_back({&TwilightDrake::instance, 1});
    deck.push_back({&SiphonSoul::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.draw();
    game.current_player().mana = 1;
    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&StarvingBuzzard::instance, 1);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().board.get_minion(0).attack == 1);
    REQUIRE(new_state.current_player().board.get_minion(1).attack == 6);
    REQUIRE(new_state.current_player().board.get_minion(2).attack == 3);

    new_state.current_player().mana = 2;
    auto post_play_state = new_state.get_possible_actions().at(0)->apply(new_state).at(0);

    REQUIRE(post_play_state.current_player().board.get_minion(0).attack == 3);

    post_play_state.current_player().mana = 4;
    auto post_post_play_state = post_play_state.get_possible_actions().at(0)->apply(post_play_state).at(0);

    REQUIRE(post_post_play_state.current_player().board.get_minion(0).attack == 4);

    post_post_play_state.current_player().mana = 6;
    auto kill_state = post_post_play_state.get_possible_actions().at(2)->apply(post_post_play_state).at(0);

    REQUIRE(kill_state.current_player().board.get_minion(1).attack == 2);
}

TEST_CASE("Starving Buzzard")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&StarvingBuzzard::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);


    game.add_minion(&StarvingBuzzard::instance, 0);
    game.add_minion(&StarvingBuzzard::instance, 1);

    REQUIRE(game.current_player().hand.size() == 4);

    game.add_minion(&BoulderfistOgre::instance, 2);
    REQUIRE(game.current_player().hand.size() == 4);
}

TEST_CASE("Arcane Golem")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&ArcaneGolem::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    SECTION("Normal use")
    {
        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().mana_crystals == 1);
    }

    SECTION("Full mana use")
    {
        game.opponent().mana_crystals = 10;

        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().mana_crystals == 10);
    }
}

TEST_CASE("Kill Command")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&KillCommand::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;
    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    SECTION("Without a beast")
    {
        auto actions = game.get_possible_actions();

        SECTION("Target ally hero")
        {
            auto new_state = actions.at(0)->apply(game).at(0);

            REQUIRE(new_state.current_player().hero->health == 27);
        }

        SECTION("Target enemy hero")
        {
            auto new_state = actions.at(2)->apply(game).at(0);

            REQUIRE(new_state.opponent().hero->health == 27);
        }

        SECTION("Target ally minion")
        {
            auto new_state = actions.at(1)->apply(game).at(0);

            REQUIRE(new_state.current_player().board.get_minion(0).health == 4);
        }

        SECTION("Target enemy hero")
        {
            auto new_state = actions.at(3)->apply(game).at(0);

            REQUIRE(new_state.opponent().board.get_minion(0).health == 4);
        }
    }

    SECTION("With a beast")
    {
        game.add_minion(&StarvingBuzzard::instance, 1);
        auto actions = game.get_possible_actions();

        SECTION("Target ally hero")
        {
            auto new_state = actions.at(0)->apply(game).at(0);

            REQUIRE(new_state.current_player().hero->health == 25);
        }

        SECTION("Target enemy hero")
        {
            auto new_state = actions.at(3)->apply(game).at(0);

            REQUIRE(new_state.opponent().hero->health == 25);
        }

        SECTION("Target ally minion")
        {
            auto new_state = actions.at(1)->apply(game).at(0);

            REQUIRE(new_state.current_player().board.get_minion(0).health == 2);
        }

        SECTION("Target enemy hero")
        {
            auto new_state = actions.at(4)->apply(game).at(0);

            REQUIRE(new_state.opponent().board.get_minion(0).health == 2);
        }
    }
}

TEST_CASE("Unleash The Hounds")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&UnleashTheHounds::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    SECTION("Opponent has more minions than you")
    {
        const unsigned expected_count = 4;

        for(unsigned i = 0; i < expected_count; ++i)
            game.add_minion(&BoulderfistOgre::instance, i, false);

        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == expected_count);
    }

    SECTION("You have more minions than the opponent")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);

        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == 2);
    }
}

TEST_CASE("Tracking")
{
    for(unsigned card_count = 0; card_count <= 3; ++card_count)
    {
        auto hero = std::make_unique<Rexxar>();
        DecklistDeck deck;
        deck.push_back({&Tracking::instance, card_count + 3});
        Decklist decklist("Test", std::move(hero), std::move(deck));
        Game game(decklist, decklist, rng);

        game.current_player().mana = 1;

        auto actions = game.get_possible_actions();

        REQUIRE(actions.size() == (card_count > 0 ? card_count : 1) * 3 + 1);

        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().hand.size() == (card_count > 0 ? 3 : 2));
        REQUIRE(new_state.current_player().deck.size() == 0);
    }
}

TEST_CASE("ExplosiveTrap")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&ExplosiveTrap::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    new_state.switch_active_player();

    new_state.add_minion(&BoulderfistOgre::instance, 0);
    new_state.add_minion(&BoulderfistOgre::instance, 1);

    SECTION("Minion attack")
    {
        new_state.current_player().board.get_minion(0).active = true;
        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 5);
        REQUIRE(post_attack_state.current_player().board.get_minion(1).health == 5);
        REQUIRE(post_attack_state.current_player().hero->health == 28);
        REQUIRE(post_attack_state.opponent().hero->health == 24);
    }

    SECTION("Dying minion attack")
    {
        auto& minion = new_state.current_player().board.get_minion(0);
        minion.health = 2;
        minion.active = true;
        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.current_player().board.minion_count() == 1);
        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 5);
        REQUIRE(post_attack_state.current_player().hero->health == 28);
        REQUIRE(post_attack_state.opponent().hero->health == 30);
    }

    SECTION("Hero attack")
    {
        new_state.current_player().hero->weapon = Weapon(&BloodFury::instance);
        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 5);
        REQUIRE(post_attack_state.current_player().board.get_minion(1).health == 5);
        REQUIRE(post_attack_state.current_player().hero->health == 28);
        REQUIRE(post_attack_state.opponent().hero->health == 27);
    }
}

TEST_CASE("Freezing Trap")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&FreezingTrap::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    new_state.switch_active_player();

    new_state.add_minion(&BoulderfistOgre::instance, 0);
    new_state.current_player().board.get_minion(0).active = true;

    auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

    REQUIRE(post_attack_state.current_player().board.minion_count() == 0);
    REQUIRE(post_attack_state.opponent().hero->health == 30);
    REQUIRE(post_attack_state.current_player().hand.size() == 6);
    REQUIRE(post_attack_state.current_player().hand.get_card(5).mana_cost(post_attack_state) == 8);
}

TEST_CASE("Misdirection")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&Misdirection::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    new_state.switch_active_player();

    SECTION("Redirect minion to own minion")
    {
        new_state.add_minion(&BoulderfistOgre::instance, 0);
        new_state.current_player().board.get_minion(0).active = true;
        new_state.add_minion(&BoulderfistOgre::instance, 1);

        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 30);
        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 1);
        REQUIRE(post_attack_state.current_player().board.get_minion(1).health == 1);
    }

    SECTION("Redirect minion to enemy minion")
    {
        new_state.add_minion(&BoulderfistOgre::instance, 0);
        new_state.current_player().board.get_minion(0).active = true;
        new_state.add_minion(&BoulderfistOgre::instance, 0, false);

        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 30);
        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 1);
        REQUIRE(post_attack_state.opponent().board.get_minion(0).health == 1);
    }

    SECTION("Redirect minion to own face")
    {
        new_state.add_minion(&BoulderfistOgre::instance, 0);
        new_state.current_player().board.get_minion(0).active = true;
        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 30);
        REQUIRE(post_attack_state.current_player().hero->health == 24);
    }

    SECTION("Redirect hero to own minion")
    {
        new_state.add_minion(&BoulderfistOgre::instance, 0);
        new_state.current_player().hero->weapon = Weapon(&BloodFury::instance);
        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 30);
        REQUIRE(post_attack_state.current_player().hero->health == 24);
        REQUIRE(post_attack_state.current_player().board.get_minion(0).health == 4);
    }

    SECTION("Redirect hero to enemy minion")
    {
        new_state.current_player().hero->weapon = Weapon(&BloodFury::instance);
        new_state.add_minion(&BoulderfistOgre::instance, 0, false);

        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 30);
        REQUIRE(post_attack_state.current_player().hero->health == 24);
        REQUIRE(post_attack_state.opponent().board.get_minion(0).health == 4);
    }

    SECTION("No redirection target")
    {
        new_state.current_player().hero->weapon = Weapon(&BloodFury::instance);

        auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

        REQUIRE(post_attack_state.opponent().hero->health == 27);
    }
}

TEST_CASE("Flare")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&Flare::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.opponent().secrets.push_back(&ExplosiveTrap::instance);
    game.opponent().secrets.push_back(&FreezingTrap::instance);
    game.opponent().secrets.push_back(&Misdirection::instance);

    game.current_player().mana = 1;
    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.opponent().secrets.empty());
    REQUIRE(new_state.current_player().hand.size() == 3);
}

TEST_CASE("Eaglehorn Bow")
{
    auto hero = std::make_unique<Rexxar>();
    DecklistDeck deck;
    deck.push_back({&EaglehornBow::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().hero->weapon = Weapon(&EaglehornBow::instance);
    game.current_player().hero->weapon->durability = 1;
    game.opponent().hero->weapon = Weapon(&EaglehornBow::instance);
    game.opponent().secrets.push_back(&ExplosiveTrap::instance);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->weapon->durability == 1);
    REQUIRE(new_state.opponent().hero->weapon->durability == 3);
}

TEST_CASE("Execute")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Execute::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0, true);
    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);
    game.opponent().board.get_minion(0).health -= 1;

    game.current_player().mana = 1;

    auto actions = game.get_possible_actions();

    REQUIRE(actions.size() == 2);

    auto new_state = actions.at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().board.minion_count() == 1);
    REQUIRE(new_state.opponent().board.minion_count() == 1);
}

TEST_CASE("Shield Slam")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&ShieldSlam::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&BoulderfistOgre::instance, 0, true);
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    game.current_player().mana = 1;
    game.current_player().hero->armour = 4;

    auto actions = game.get_possible_actions();

    SECTION("Target ally")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).health == 3);
    }

    SECTION("Target enemy")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 3);
    }
}

TEST_CASE("Whirlwind")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Whirlwind::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 1;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().board.get_minion(0).health == 6);
    REQUIRE(new_state.current_player().board.get_minion(1).health == 6);
    REQUIRE(new_state.opponent().board.get_minion(0).health == 6);
    REQUIRE(new_state.opponent().board.get_minion(1).health == 6);
}

TEST_CASE("Armorsmith")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Armorsmith::instance, 1});
    deck.push_back({&Hellfire::instance, 2});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    new_state.current_player().mana = 4;

    auto post_hellfire_state = new_state.get_possible_actions().at(0)->apply(new_state).at(0);

    REQUIRE(post_hellfire_state.current_player().hero->health == 27);
    REQUIRE(post_hellfire_state.current_player().hero->armour == 3);
}

TEST_CASE("Cruel Taskmaster")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&CruelTaskmaster::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    SECTION("No target")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(actions.size() == 3);
    }

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    auto actions = game.get_possible_actions();

    SECTION("Target ally minion")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(1).attack == 8);
        REQUIRE(new_state.current_player().board.get_minion(1).health == 6);
    }

    SECTION("Target enemy minion")
    {
        auto new_state = actions.at(1)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).attack == 8);
        REQUIRE(new_state.opponent().board.get_minion(0).health == 6);
    }
}

TEST_CASE("Slam")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Slam::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 2;

    SECTION("Target ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);
        game.current_player().board.get_minion(0).health = 2;

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hand.size() == 2);
    }

    SECTION("Draw card from ally")
    {
        game.add_minion(&BoulderfistOgre::instance, 0);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.get_minion(0).health == 5);
        REQUIRE(new_state.current_player().hand.size() == 3);
    }

    SECTION("Target enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);
        game.opponent().board.get_minion(0).health = 2;

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.minion_count() == 0);
        REQUIRE(new_state.current_player().hand.size() == 2);
    }

    SECTION("Draw card from enemy")
    {
        game.add_minion(&BoulderfistOgre::instance, 0, false);

        auto actions = game.get_possible_actions();
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.get_minion(0).health == 5);
        REQUIRE(new_state.current_player().hand.size() == 3);
    }
}

TEST_CASE("Acolyte of Pain")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&AcolyteOfPain::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    game.add_minion(&AcolyteOfPain::instance, 0);

    auto& acolyte = game.current_player().board.get_minion(0);

    acolyte.deal_dmg(1, game);
    acolyte.deal_dmg(1, game);

    REQUIRE(game.current_player().hand.size() == 5);
}

TEST_CASE("Big Game Hunter")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&BigGameHunter::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    SECTION("No target")
    {
        auto actions = game.get_possible_actions();
        REQUIRE(actions.size() == 3);
    }

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);
    game.current_player().board.get_minion(0).attack += 1;
    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);
    game.opponent().board.get_minion(0).attack += 1;

    auto actions = game.get_possible_actions();

    REQUIRE(actions.size() == 8);

    SECTION("Kill ally minion")
    {
        auto new_state = actions.at(0)->apply(game).at(0);

        REQUIRE(new_state.current_player().board.minion_count() == 2);
    }

    SECTION("Kill enemy minion")
    {
        auto new_state = actions.at(3)->apply(game).at(0);

        REQUIRE(new_state.opponent().board.minion_count() == 1);
    }
}

TEST_CASE("Shield Block")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&ShieldBlock::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 3;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().hero->armour == 5);
    REQUIRE(new_state.current_player().hand.size() == 3);
}

TEST_CASE("Azure Drake")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&AzureDrake::instance, 1});
    deck.push_back({&SiphonSoul::instance, 4});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 5;

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(new_state.current_player().spell_damage == 1);
    REQUIRE(new_state.current_player().hand.size() == 3);

    new_state.current_player().hand.add_cards(&Whirlwind::instance);
    new_state.current_player().mana = 1;

    auto post_whirlwind_state = new_state.get_possible_actions().at(0)->apply(new_state).at(0);

    REQUIRE(post_whirlwind_state.current_player().board.get_minion(0).health == 2);

    post_whirlwind_state.current_player().mana = 6;

    auto post_kill_state = post_whirlwind_state.get_possible_actions().at(0)->apply(post_whirlwind_state).at(0);

    REQUIRE(post_kill_state.current_player().spell_damage == 0);
}

TEST_CASE("Brawl")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Brawl::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    SECTION("No minions")
    {
        game.current_player().mana = 5;

        auto actions = game.get_possible_actions();

        REQUIRE(actions.size() == 3);

        REQUIRE(actions.at(0)->apply(game).size() == 1);
    }

    SECTION("Some minions")
    {
        game.current_player().mana = 5;
        game.add_minion(&BoulderfistOgre::instance, 0);
        game.add_minion(&BoulderfistOgre::instance, 1);
        game.add_minion(&BoulderfistOgre::instance, 0, false);
        game.add_minion(&BoulderfistOgre::instance, 1, false);

        auto new_states = game.get_possible_actions().at(0)->apply(game);

        REQUIRE(new_states.size() == 4);

        REQUIRE(new_states.at(0).current_player().board.minion_count() == 1);
        REQUIRE(new_states.at(1).current_player().board.minion_count() == 1);
        REQUIRE(new_states.at(2).opponent().board.minion_count() == 1);
        REQUIRE(new_states.at(3).opponent().board.minion_count() == 1);
    }
}

TEST_CASE("Cairne Bloodhoof")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&CairneBloodhoof::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 6;
    game.add_minion(&BoulderfistOgre::instance, 0, false);

    auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

    new_state.current_player().board.get_minion(0).active = true;

    auto post_attack_state = new_state.get_possible_actions().at(1)->apply(new_state).at(0);

    REQUIRE(post_attack_state.current_player().board.minion_count() == 1);
    REQUIRE(post_attack_state.opponent().board.get_minion(0).health == 3);
}

TEST_CASE("Sylvanas Windrunner")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&SylvanasWindrunner::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    SECTION("Nothing to steal")
    {
        game.current_player().mana = 6;
        REQUIRE(game.get_possible_actions().at(0)->apply(game).size() == 1);
    }

    SECTION("Something to steal")
    {
        game.current_player().mana = 6;
        game.add_minion(&BoulderfistOgre::instance, 0, false);
        game.opponent().board.get_minion(0).health = 5;

        game.switch_active_player();
        game.add_minion(&AzureDrake::instance, 1);
        game.switch_active_player();
        game.opponent().board.get_minion(1).active = true;

        game.add_minion(&LeeroyJenkins::instance, 2, false);

        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);

        new_state.current_player().board.get_minion(0).active = true;

        auto post_attack_states = new_state.get_possible_actions().at(1)->apply(new_state);

        REQUIRE(post_attack_states.size() == 2);

        REQUIRE(post_attack_states.at(0).current_player().board.minion_count() == 1);
        REQUIRE(post_attack_states.at(0).opponent().board.minion_count() == 1);
        REQUIRE(post_attack_states.at(0).current_player().board.get_minion(0).active == false);
        REQUIRE(post_attack_states.at(0).opponent().spell_damage == 0);
        REQUIRE(post_attack_states.at(0).current_player().spell_damage == 1);

        REQUIRE(post_attack_states.at(1).current_player().board.minion_count() == 1);
        REQUIRE(post_attack_states.at(1).opponent().board.minion_count() == 1);
        REQUIRE(post_attack_states.at(1).current_player().board.get_minion(0).active == true);
    }
}

TEST_CASE("Baron Geddon")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&BaronGeddon::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 7;

    game.add_minion(&BoulderfistOgre::instance, 0);
    game.add_minion(&BoulderfistOgre::instance, 1);

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto actions = game.get_possible_actions();

    auto new_state = actions.at(0)->apply(game).at(0);

    auto eot_state = new_state.get_possible_actions().at(0)->apply(new_state).at(0);

    REQUIRE(eot_state.current_player().hero->health == 28);
    REQUIRE(eot_state.opponent().hero->health == 28);
    REQUIRE(eot_state.current_player().board.get_minion(0).health == 5);
    REQUIRE(eot_state.current_player().board.get_minion(1).health == 5);
    REQUIRE(eot_state.current_player().board.get_minion(2).health == 5);
    REQUIRE(eot_state.opponent().board.get_minion(0).health == 5);
    REQUIRE(eot_state.opponent().board.get_minion(1).health == 5);
}

TEST_CASE("Grommash Hellscream")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Whirlwind::instance, 1});
    deck.push_back({&EarthenRingFarseer::instance, 1});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.add_minion(&GrommashHellscream::instance, 0);

    game.current_player().mana = 1;

    auto post_dmg_state = game.get_possible_actions().at(0)->apply(game).at(0);

    REQUIRE(post_dmg_state.current_player().board.get_minion(0).attack == 10);

    post_dmg_state.current_player().mana = 3;
    auto post_heal_state = post_dmg_state.get_possible_actions().at(1)->apply(post_dmg_state).at(0);

    REQUIRE(post_heal_state.current_player().board.get_minion(1).attack == 4);
}

TEST_CASE("Ragnaros The Firelord")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&RagnarosTheFirelord::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 8;

    game.add_minion(&BoulderfistOgre::instance, 0, false);
    game.add_minion(&BoulderfistOgre::instance, 1, false);

    auto actions = game.get_possible_actions();

    auto new_state = actions.at(0)->apply(game).at(0);

    auto eot_states = new_state.get_possible_actions().at(0)->apply(new_state);

    REQUIRE(eot_states.size() == 3);


    REQUIRE(eot_states.at(0).opponent().hero->health == 22);
    REQUIRE(eot_states.at(1).opponent().board.minion_count() == 1);
    REQUIRE(eot_states.at(2).opponent().board.minion_count() == 1);
}

TEST_CASE("Alexstraza")
{
    auto hero = std::make_unique<GarroshHellscream>();
    DecklistDeck deck;
    deck.push_back({&Alexstraza::instance, 5});
    Decklist decklist("Test", std::move(hero), std::move(deck));
    Game game(decklist, decklist, rng);

    game.current_player().mana = 9;

    SECTION("Target ally")
    {
        auto new_state = game.get_possible_actions().at(0)->apply(game).at(0);
        REQUIRE(new_state.current_player().hero->health == 15);
    }

    SECTION("Target enemy")
    {
        auto new_state = game.get_possible_actions().at(1)->apply(game).at(0);
        REQUIRE(new_state.opponent().hero->health == 15);
    }
}
