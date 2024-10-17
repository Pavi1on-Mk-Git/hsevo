#ifndef ANCIENT_WATCHER_H
#define ANCIENT_WATCHER_H

#include "logic/cards/MinionCard.h"

class AncientWatcher: public MinionCard
{
private:
    AncientWatcher(): MinionCard("Ancient Watcher", 2, 4, 5, CANT_ATTACK) {}
public:
    static const AncientWatcher instance;
};

inline const AncientWatcher AncientWatcher::instance;

#endif