#ifndef CARD_DEFINITIONS_H
#define CARD_DEFINITIONS_H

#include "logic/Card.h"

extern const Card BOULDERFIST_OGRE;
extern const Card ANCIENT_WATCHER;

void sunfury_protector_on_play(Game& game, std::vector<OnPlayArg> args);
std::vector<std::unique_ptr<PlayCardAction>> sunfury_protector_create_play_actions(
    const std::unique_ptr<Card>& self, Game& game, unsigned hand_position
);

extern const Card SUNFURY_PROTECTOR;

#endif