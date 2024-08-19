#ifndef CARD_DEFINITIONS_H
#define CARD_DEFINITIONS_H

#include "logic/Card.h"

/*
General on_play / create_play_actions functions
*/

std::vector<std::unique_ptr<PlayCardAction>> single_arg_self_play_position_create_play_actions(
    const std::unique_ptr<Card>& self, const Game& game, unsigned hand_position
);

/*
Concrete on_play / create_play_actions functions for specific cards
*/

void sunfury_protector_on_play(Game& game, std::vector<OnPlayArg> args);
void earthen_ring_farseer_on_play(Game& game, std::vector<OnPlayArg> args);
std::vector<std::unique_ptr<PlayCardAction>> earthen_ring_farseer_create_play_actions(
    const std::unique_ptr<Card>& self, const Game& game, unsigned hand_position
);
void defender_of_argus_on_play(Game& game, std::vector<OnPlayArg> args);
void leeroy_jenkins_on_play(Game& game, std::vector<OnPlayArg> args);
void twilight_drake_on_play(Game& game, std::vector<OnPlayArg> args);
void faceless_manipulator_on_play(Game& game, std::vector<OnPlayArg> args);
std::vector<std::unique_ptr<PlayCardAction>> faceless_manipulator_create_play_actions(
    const std::unique_ptr<Card>& self, const Game& game, unsigned hand_position
);

/*
Special mana cost functions
*/

unsigned mountain_giant_mana_cost(const std::unique_ptr<Card>& self, const Game& game);
unsigned molten_giant_mana_cost(const std::unique_ptr<Card>& self, const Game& game);

/*
Card declarations
*/

extern const Card BOULDERFIST_OGRE;
extern const Card ANCIENT_WATCHER;
extern const Card SUNFURY_PROTECTOR;
extern const Card EARTHEN_RING_FARSEER;
extern const Card DEFENDER_OF_ARGUS;
extern const Card LEEROY_JENKINS;
extern const Card TWILIGHT_DRAKE;
extern const Card FACELESS_MANIPULATOR;
extern const Card MOUNTAIN_GIANT;
extern const Card MOLTEN_GIANT;

/*
Token declarations
*/

extern const Card WHELP;

#endif