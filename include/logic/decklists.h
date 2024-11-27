#ifndef DECKLISTS_H
#define DECKLISTS_H

#include "logic/Decklist.h"

Decklist ogre_deck();
Decklist handlock();
Decklist face_hunter();
Decklist control_warrior();

std::vector<Decklist> get_decklists();

#endif
