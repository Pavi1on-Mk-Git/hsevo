#ifndef DECK_SELECTION_H
#define DECK_SELECTION_H

#include <raylib-cpp.hpp>

#include "logic/Decklist.h"

class DeckSelection
{
private:
    raylib::Window& window_;
    std::vector<const Decklist*> decklists_;
    const Decklist* player_deck_;
    const Decklist* bot_deck_;
    std::vector<raylib::Rectangle> deck_choice_buttons_;

    void update();
    void draw();
public:
    DeckSelection(raylib::Window& window, const std::vector<const Decklist*>& decklists);
    std::pair<const Decklist*, const Decklist*> run();
};

#endif