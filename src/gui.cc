#include <chrono>
#include <fstream>
#include <raylib-cpp.hpp>

#include "gui/DeckSelection.h"
#include "gui/GameGui.h"
#include "logic/decklists.h"
#include "utils/Rng.h"

int main()
{
    Rng::instance().seed(std::chrono::system_clock::now().time_since_epoch().count());
    raylib::Window window(1280, 720);
    window.SetTargetFPS(60);

    const Decklist OGRE_DECK = ogre_deck(), HANDLOCK = handlock();

    DeckSelection selection(window, {&OGRE_DECK, &HANDLOCK});
    auto [player_deck, bot_deck] = selection.run();
    std::ifstream in("results/test.txt");
    GameGui gui(window, player_deck, bot_deck, in);
    gui.run();
}
