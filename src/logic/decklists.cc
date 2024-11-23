#include "logic/decklists.h"

#include "logic/cards/AbusiveSergeant.h"
#include "logic/cards/AcolyteOfPain.h"
#include "logic/cards/AncientWatcher.h"
#include "logic/cards/ArcaneGolem.h"
#include "logic/cards/Armorsmith.h"
#include "logic/cards/AzureDrake.h"
#include "logic/cards/BaronGeddon.h"
#include "logic/cards/BigGameHunter.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/cards/Brawl.h"
#include "logic/cards/CairneBloodhoof.h"
#include "logic/cards/CruelTaskmaster.h"
#include "logic/cards/DefenderOfArgus.h"
#include "logic/cards/EaglehornBow.h"
#include "logic/cards/EarthenRingFarseer.h"
#include "logic/cards/Execute.h"
#include "logic/cards/ExplosiveTrap.h"
#include "logic/cards/FacelessManipulator.h"
#include "logic/cards/FieryWarAxe.h"
#include "logic/cards/Flare.h"
#include "logic/cards/FreezingTrap.h"
#include "logic/cards/GrommashHellscream.h"
#include "logic/cards/Hellfire.h"
#include "logic/cards/HuntersMark.h"
#include "logic/cards/KillCommand.h"
#include "logic/cards/KorkronElite.h"
#include "logic/cards/LeeroyJenkins.h"
#include "logic/cards/LeperGnome.h"
#include "logic/cards/LordJaraxxusCard.h"
#include "logic/cards/Misdirection.h"
#include "logic/cards/MoltenGiant.h"
#include "logic/cards/MortalCoil.h"
#include "logic/cards/MountainGiant.h"
#include "logic/cards/PowerOverwhelming.h"
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
#include "logic/cards/Wolfrider.h"
#include "logic/heroes/GarroshHellscream.h"
#include "logic/heroes/GulDan.h"
#include "logic/heroes/Rexxar.h"

Decklist ogre_deck()
{
    std::unique_ptr<Hero> hero = std::make_unique<GulDan>();

    DecklistDeck deck;
    deck.emplace_back(&BoulderfistOgre::instance, 30);

    return Decklist("Ogre deck", std::move(hero), deck);
}

Decklist handlock()
{
    std::unique_ptr<Hero> hero = std::make_unique<GulDan>();

    DecklistDeck deck;
    deck.emplace_back(&SacrificialPact::instance, 1);
    deck.emplace_back(&Soulfire::instance, 2);
    deck.emplace_back(&MortalCoil::instance, 2);
    deck.emplace_back(&PowerOverwhelming::instance, 2);
    deck.emplace_back(&AncientWatcher::instance, 2);
    deck.emplace_back(&SunfuryProtector::instance, 2);
    deck.emplace_back(&EarthenRingFarseer::instance, 2);
    deck.emplace_back(&DefenderOfArgus::instance, 2);
    deck.emplace_back(&Hellfire::instance, 2);
    deck.emplace_back(&LeeroyJenkins::instance, 1);
    deck.emplace_back(&Shadowflame::instance, 2);
    deck.emplace_back(&TwilightDrake::instance, 2);
    deck.emplace_back(&FacelessManipulator::instance, 2);
    deck.emplace_back(&SiphonSoul::instance, 2);
    deck.emplace_back(&LordJaraxxusCard::instance, 1);
    deck.emplace_back(&MountainGiant::instance, 2);
    deck.emplace_back(&MoltenGiant::instance, 2);

    return Decklist("Handlock", std::move(hero), deck);
}

Decklist face_hunter()
{
    std::unique_ptr<Hero> hero = std::make_unique<Rexxar>();

    DecklistDeck deck;
    deck.emplace_back(&HuntersMark::instance, 2);
    deck.emplace_back(&AbusiveSergeant::instance, 2);
    deck.emplace_back(&Flare::instance, 1);
    deck.emplace_back(&LeperGnome::instance, 2);
    deck.emplace_back(&TimberWolf::instance, 2);
    deck.emplace_back(&Tracking::instance, 2);
    deck.emplace_back(&ExplosiveTrap::instance, 2);
    deck.emplace_back(&FreezingTrap::instance, 2);
    deck.emplace_back(&Misdirection::instance, 2);
    deck.emplace_back(&StarvingBuzzard::instance, 2);
    deck.emplace_back(&EaglehornBow::instance, 2);
    deck.emplace_back(&ArcaneGolem::instance, 2);
    deck.emplace_back(&KillCommand::instance, 2);
    deck.emplace_back(&UnleashTheHounds::instance, 2);
    deck.emplace_back(&Wolfrider::instance, 2);
    deck.emplace_back(&LeeroyJenkins::instance, 1);

    return Decklist("Face Hunter", std::move(hero), deck);
}

Decklist control_warrior()
{
    std::unique_ptr<Hero> hero = std::make_unique<GarroshHellscream>();

    DecklistDeck deck;
    deck.emplace_back(&Execute::instance, 2);
    deck.emplace_back(&ShieldSlam::instance, 2);
    deck.emplace_back(&Whirlwind::instance, 2);
    deck.emplace_back(&Armorsmith::instance, 2);
    deck.emplace_back(&CruelTaskmaster::instance, 2);
    deck.emplace_back(&FieryWarAxe::instance, 2);
    deck.emplace_back(&Slam::instance, 2);
    deck.emplace_back(&AcolyteOfPain::instance, 2);
    deck.emplace_back(&BigGameHunter::instance, 1);
    deck.emplace_back(&ShieldBlock::instance, 2);
    deck.emplace_back(&KorkronElite::instance, 2);
    deck.emplace_back(&AzureDrake::instance, 2);
    deck.emplace_back(&Brawl::instance, 1);
    deck.emplace_back(&CairneBloodhoof::instance, 1);
    deck.emplace_back(&SylvanasWindrunner::instance, 1);
    deck.emplace_back(&BaronGeddon::instance, 1);
    deck.emplace_back(&GrommashHellscream::instance, 1);

    return Decklist("Control Warrior", std::move(hero), deck);
}
