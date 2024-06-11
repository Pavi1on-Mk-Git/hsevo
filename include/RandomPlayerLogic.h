#ifndef RANDOM_PLAYER_LOGIC_H
#define RANDOM_PLAYER_LOGIC_H

#include <memory>
#include <random>

#include "Action.h"
#include "decklists.h"

struct RandomPlayerLogic
{
    std::ranlux24_base& random_engine;
    const DeckList& decklist;
    RandomPlayerLogic(const DeckList& decklist, std::ranlux24_base& random_engine);
    std::unique_ptr<Action> choose_action(std::vector<std::unique_ptr<Action>> actions) const;
};

#endif