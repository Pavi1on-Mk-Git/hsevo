#include "logic/Player.h"

Player::Player(const std::unique_ptr<PlayerLogic>& logic): logic(logic), hero(logic->decklist) {}