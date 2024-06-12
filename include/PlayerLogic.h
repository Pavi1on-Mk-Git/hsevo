#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H

#include <memory>

#include "Action.h"
#include "decklists.h"

struct PlayerLogic
{
    const DeckList& decklist;

    PlayerLogic(const DeckList& decklist): decklist(decklist) {}

    virtual std::unique_ptr<Action> choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
        const = 0;
};


#endif