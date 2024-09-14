#ifndef ANCIENT_WATCHER_H
#define ANCIENT_WATCHER_H

#include "logic/cards/MinionCard.h"

struct AncientWatcher: public MinionCard
{
    AncientWatcher(): MinionCard("Ancient Watcher", 2, 4, 5, CANT_ATTACK) {}

    CLONE_CARD
};

#endif