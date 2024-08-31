#include "logic/Player.h"

Player::Player(std::shared_ptr<PlayerLogic> logic): logic(logic), hero(logic->decklist) {}