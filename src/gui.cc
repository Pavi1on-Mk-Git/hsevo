#include <chrono>
#include <fstream>
#include <raylib-cpp.hpp>
#include <spdlog/spdlog.h>

#include "gui/DeckSelection.h"
#include "gui/GameGui.h"
#include "logic/decklists.h"
#include "utils/Rng.h"

int main()
{
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    Rng::instance().seed(seed);
    SPDLOG_DEBUG("Game played with seed: {}", seed);

    raylib::Window window(1280, 720);
    window.SetTargetFPS(60);

    const Decklist OGRE_DECK = ogre_deck(), HANDLOCK = handlock();
    const std::vector<const Decklist*> decklists{&OGRE_DECK, &HANDLOCK};

    std::ifstream OGRE_LOGIC("results/test.txt"), HANDLOCK_LOGIC("results/test.txt");
    const std::vector<std::ifstream*> logic_files{&OGRE_LOGIC, &HANDLOCK_LOGIC};

    DeckSelection selection(window, decklists, logic_files);
    auto [player_deck, bot_deck, bot_logic_file] = selection.run();
    GameGui gui(window, player_deck, bot_deck, *bot_logic_file);
    gui.run();
}
