#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H

#include <memory>

#include "logic/Action.h"
#include "logic/decklists.h"

class PlayerLogic
{
protected:
    PlayerLogic(const Decklist& decklist): decklist(decklist) {}
public:
    const Decklist& decklist;

    virtual ~PlayerLogic() = default;
    virtual Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions)
        const = 0;
};


#endif