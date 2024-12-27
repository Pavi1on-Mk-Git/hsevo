#ifndef DECKLISTS_H
#define DECKLISTS_H

#include "logic/Decklist.h"

/**
 * Test decklist containing 30 copies of Boulderfist Ogre
 */
Decklist ogre_deck();

/**
 * Deck sourced from:
 * https://hearthstone-decks.net/hand-warlock-152-legend-di4mond-score-39-8/
 */
Decklist handlock();

/**
 * Deck sourced from:
 * https://hearthstone-decks.net/face-hunter-5-legend-darklumiya/
 */
Decklist face_hunter();

/**
 * Deck sourced from:
 * https://hearthstone-decks.net/control-warrior-17-legend-shotlon/
 */
Decklist control_warrior();

/**
 * Amount of decks to be used in the experiments
 */
const unsigned DECK_COUNT = 3;

/**
 * Get all decklists to be used in the experiments
 */
std::array<Decklist, DECK_COUNT> get_decklists();

#endif
