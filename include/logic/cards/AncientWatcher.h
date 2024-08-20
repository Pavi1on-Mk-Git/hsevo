#ifndef ANCIENT_WATCHER_H
#define ANCIENT_WATCHER_H

#include "logic/cards/Card.h"

struct AncientWatcher: public Card
{
    AncientWatcher(): Card("Ancient Watcher", 2, 4, 5, CANT_ATTACK) {}
};

#endif