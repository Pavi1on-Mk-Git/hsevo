#include "gui/GuiPlayerLogic.h"

#include <raylib-cpp.hpp>

#include "gui/GameGui.h"
#include "logic/Game.h"

GuiPlayerLogic::GuiPlayerLogic(const Decklist& decklist, GameGui& gui): PlayerLogic(decklist), gui_(gui) {}

Game GuiPlayerLogic::choose_and_apply_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
{
    if(!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return game;

    auto potential_elements = GameGui::actions_to_elements(actions, click_sequence);

    return game;
}