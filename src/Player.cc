#include "Player.h"

Player::Player(const RandomPlayerLogic& logic): logic(logic), state(logic.decklist, logic.random_engine) {}