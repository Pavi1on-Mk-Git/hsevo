#ifndef GUI_PLAYER_LOGIC_H
#define GUI_PLAYER_LOGIC_H

#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"

struct GameGui;

class GuiPlayerLogic: public PlayerLogic
{
private:
    GameGui& gui_;
    std::deque<GuiElementId> click_sequence;
public:
    GuiPlayerLogic(const Decklist& decklist, GameGui& gui);
    Game choose_and_apply_action(const Game& game, std::vector<std::unique_ptr<Action>> actions) override;
};

#endif