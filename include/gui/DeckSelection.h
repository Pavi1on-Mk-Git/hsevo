#ifndef DECK_SELECTION_H
#define DECK_SELECTION_H

#include <raylib-cpp.hpp>

#include "logic/Decklist.h"

class DeckSelection
{
private:
    raylib::Window& window_;
    std::vector<const Decklist*> decklists_;
    std::vector<std::ifstream*> logic_files_;
    const Decklist* player_deck_;
    const Decklist* bot_deck_;
    std::ifstream* bot_logic_file_;
    std::vector<raylib::Rectangle> deck_choice_buttons_;
    std::vector<bool> button_is_highlighted;

    void update();
    void draw();
public:
    DeckSelection(
        raylib::Window& window, const std::vector<const Decklist*>& decklists,
        const std::vector<std::ifstream*>& logic_files
    );
    std::tuple<const Decklist*, const Decklist*, std::ifstream*> run();
};

#endif