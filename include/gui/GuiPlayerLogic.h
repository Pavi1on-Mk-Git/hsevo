#ifndef GUI_PLAYER_LOGIC_H
#define GUI_PLAYER_LOGIC_H

#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"
#include "utils/Rng.h"

struct GameGui;

class GuiPlayerLogic: public PlayerLogic
{
private:
    GameGui& gui_;
    Rng& rng_;
    mutable std::deque<GuiElementId> click_sequence_;
public:
    GuiPlayerLogic(const Decklist& decklist, GameGui& gui, Rng& rng);
    Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions) const override;
};

#endif