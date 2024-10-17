#include "logic/decklists.h"

#include "logic/cards/AncientWatcher.h"
#include "logic/cards/BoulderfistOgre.h"
#include "logic/cards/DefenderOfArgus.h"
#include "logic/cards/EarthenRingFarseer.h"
#include "logic/cards/FacelessManipulator.h"
#include "logic/cards/Hellfire.h"
#include "logic/cards/LeeroyJenkins.h"
#include "logic/cards/LordJaraxxusCard.h"
#include "logic/cards/MoltenGiant.h"
#include "logic/cards/MortalCoil.h"
#include "logic/cards/MountainGiant.h"
#include "logic/cards/PowerOverwhelming.h"
#include "logic/cards/SacrificialPact.h"
#include "logic/cards/Shadowflame.h"
#include "logic/cards/SiphonSoul.h"
#include "logic/cards/Soulfire.h"
#include "logic/cards/SunfuryProtector.h"
#include "logic/cards/TwilightDrake.h"
#include "logic/heroes/GulDan.h"

Decklist ogre_deck()
{
    std::unique_ptr<Hero> hero = std::make_unique<GulDan>();

    DecklistDeck deck;
    deck.emplace_back(&BoulderfistOgre::instance, 30);

    return Decklist(std::move(hero), std::move(deck));
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

    return Decklist(std::move(hero), std::move(deck));
}