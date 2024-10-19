#include <raylib-cpp.hpp>

#include "gui/DeckSelection.h"
#include "logic/decklists.h"

int main()
{
    raylib::Window window(1280, 720);
    window.SetTargetFPS(60);

    const Decklist OGRE_DECK = ogre_deck(), HANDLOCK = handlock();

    DeckSelection selection(window, {&OGRE_DECK, &HANDLOCK});
    selection.run();
}
