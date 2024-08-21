#ifndef DECKLISTS_H
#define DECKLISTS_H

#include <vector>

#include "logic/cards/Card.h"

using Decklist = std::vector<std::pair<std::unique_ptr<Card>, unsigned>>;

Decklist ogre_deck();

#endif