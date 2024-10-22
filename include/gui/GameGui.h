#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <deque>
#include <raylib-cpp.hpp>

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

    void update();
    void update_begin_turn();
    GuiElementId mouse_position();
    void draw();
    // void draw_hero(const Hero& hero, bool is_player_side);
    // void draw_minion(const Minion& minion, bool is_player_side);
    // void draw_card(const Card* const& card, bool is_player_side);
    // void draw_deck(unsigned size, bool is_player_side);
    // void draw_eot_button();
public:
    GameGui(raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& in);
    GameResult run();
    static std::vector<std::deque<GuiElementId>> actions_to_elements(
        const std::vector<std::unique_ptr<Action>>& actions, const std::deque<GuiElementId>& clicked_elements
    );
};

#endif