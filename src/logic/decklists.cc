#include "logic/decklists.h"

#include "logic/cards/AbusiveSergeant.h"
#include "logic/cards/AncientWatcher.h"
#include "logic/cards/ArcaneGolem.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/cards/DefenderOfArgus.h"
#include "logic/cards/EarthenRingFarseer.h"
#include "logic/cards/FacelessManipulator.h"
#include "logic/cards/Hellfire.h"
#include "logic/cards/HuntersMark.h"
#include "logic/cards/KillCommand.h"
#include "logic/cards/LeeroyJenkins.h"
#include "logic/cards/LeperGnome.h"
#include "logic/cards/LordJaraxxusCard.h"
#include "logic/cards/MoltenGiant.h"
#include "logic/cards/MortalCoil.h"
#include "logic/cards/MountainGiant.h"
#include "logic/cards/PowerOverwhelming.h"
#include "logic/cards/SacrificialPact.h"
#include "logic/cards/Shadowflame.h"
#include "logic/cards/SiphonSoul.h"
#include "logic/cards/Soulfire.h"
#include "logic/cards/StarvingBuzzard.h"
#include "logic/cards/SunfuryProtector.h"
#include "logic/cards/TimberWolf.h"
#include "logic/cards/TwilightDrake.h"
#include "logic/cards/UnleashTheHounds.h"
#include "logic/cards/Wolfrider.h"
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
    deck.emplace_back(&LeperGnome::instance, 2);
    deck.emplace_back(&TimberWolf::instance, 2);
    deck.emplace_back(&StarvingBuzzard::instance, 2);
    deck.emplace_back(&ArcaneGolem::instance, 2);
    deck.emplace_back(&KillCommand::instance, 2);
    deck.emplace_back(&UnleashTheHounds::instance, 2);
    deck.emplace_back(&Wolfrider::instance, 2);
    deck.emplace_back(&LeeroyJenkins::instance, 1);

    return Decklist("Face Hunter", std::move(hero), deck);
}
