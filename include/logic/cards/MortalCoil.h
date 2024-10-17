#ifndef MORTAL_COIL_H
#define MORTAL_COIL_H

#include "logic/cards/SingleArgTargetMinionCard.h"

class MortalCoil: public SingleArgTargetMinionCard
{
private:
    MortalCoil(): SingleArgTargetMinionCard("Mortal Coil", 1) {}
public:
    static const MortalCoil instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const MortalCoil MortalCoil::instance;

#endif