#include "Player.h"

Player::Player(const std::unique_ptr<PlayerLogic>& logic, std::ranlux24_base& random_engine):
    logic(logic), state(logic->decklist, random_engine)
{}