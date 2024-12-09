#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <future>
#include <raylib-cpp.hpp>

#include "gui/GuiElement.h"
#include "logic/Game.h"
#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"

class GameGui

{
private:
    raylib::Window& window_;
    const bool is_bot_first_;
    bool is_turn_started_;
    std::unique_ptr<const PlayerLogic> player_logic_, bot_logic_;
    Game game_;
    std::optional<GameResult> winner_;
    unsigned current_turn_;
    std::vector<std::unique_ptr<GuiElement>> elements_;
    std::future<Game> bot_action_result_;

    void update();
    void update_begin_turn();
    Game delayed_action();
    void draw();
public:
    std::optional<unsigned> minion_gap_position;

    GameGui(
        raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& bot_logic_file,
        Rng& rng
    );
    GameResult run();
    bool is_player_turn() const;
    raylib::Rectangle scale(const raylib::Rectangle& original) const;
    std::optional<GuiElementId> clicked_element() const;
    void make_active(const std::vector<std::deque<GuiElementId>> potential_sequences = {});
};

#endif