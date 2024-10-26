#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <raylib-cpp.hpp>

#include "gui/GuiElement.h"
#include "logic/Game.h"
#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"

class GameGui

{
private:
    raylib::Window& window_;
    bool is_bot_first_;
    bool is_turn_started_;
    std::unique_ptr<PlayerLogic> player_logic_, bot_logic_;
    Game game_;
    std::optional<GameResult> winner_;
    unsigned current_turn_;
    std::vector<std::unique_ptr<GuiElement>> elements_;

    void update();
    void update_begin_turn();
    void draw();
public:
    GameGui(raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& in);
    GameResult run();
    bool is_player_turn() const;
    raylib::Rectangle scale(const raylib::Rectangle& original) const;
    std::optional<GuiElementId> clicked_element() const;
};

#endif