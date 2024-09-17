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
    deck.emplace_back(std::make_unique<BoulderfistOgre>(), 30);

    return Decklist(std::move(hero), std::move(deck));
}

Decklist handlock()
{
    std::unique_ptr<Hero> hero = std::make_unique<GulDan>();

    DecklistDeck deck;
    deck.emplace_back(std::make_unique<SacrificialPact>(), 1);
    deck.emplace_back(std::make_unique<Soulfire>(), 2);
    deck.emplace_back(std::make_unique<MortalCoil>(), 2);
    deck.emplace_back(std::make_unique<PowerOverwhelming>(), 2);
    deck.emplace_back(std::make_unique<AncientWatcher>(), 2);
    deck.emplace_back(std::make_unique<SunfuryProtector>(), 2);
    deck.emplace_back(std::make_unique<EarthenRingFarseer>(), 2);
    deck.emplace_back(std::make_unique<DefenderOfArgus>(), 2);
    deck.emplace_back(std::make_unique<Hellfire>(), 2);
    deck.emplace_back(std::make_unique<LeeroyJenkins>(), 1);
    deck.emplace_back(std::make_unique<Shadowflame>(), 2);
    deck.emplace_back(std::make_unique<TwilightDrake>(), 2);
    deck.emplace_back(std::make_unique<FacelessManipulator>(), 2);
    deck.emplace_back(std::make_unique<SiphonSoul>(), 2);
    deck.emplace_back(std::make_unique<LordJaraxxusCard>(), 1);
    deck.emplace_back(std::make_unique<MountainGiant>(), 2);
    deck.emplace_back(std::make_unique<MoltenGiant>(), 2);

    return Decklist(std::move(hero), std::move(deck));
}