#include "Player.h"

Player::Player(const std::unique_ptr<PlayerLogic>& logic): logic(logic), state(logic->decklist) {}