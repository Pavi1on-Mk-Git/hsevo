#ifndef DECKLISTS_H
#define DECKLISTS_H

#include "logic/Decklist.h"

Decklist ogre_deck();
Decklist handlock();
Decklist face_hunter();
Decklist control_warrior();

const unsigned DECK_COUNT = 3;

std::array<Decklist, DECK_COUNT> get_decklists();

#endif
