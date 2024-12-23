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
    raylib::Window window(1280, 720);
    window.SetTargetFPS(60);

    const Decklist HANDLOCK = handlock(), FACE_HUNTER = face_hunter(), CONTROL_WARRIOR = control_warrior();
    const std::vector<const Decklist*> decklists{&HANDLOCK, &FACE_HUNTER, &CONTROL_WARRIOR};

    std::ifstream HANDLOCK_LOGIC("gui_player_logics/warlock.txt"), FACE_HUNTER_LOGIC("gui_player_logics/hunter.txt"),
        CONTROL_WARRIOR_LOGIC("gui_player_logics/warrior.txt");
    const std::vector<std::ifstream*> logic_files{&HANDLOCK_LOGIC, &FACE_HUNTER_LOGIC, &CONTROL_WARRIOR_LOGIC};

    DeckSelection selection(window, decklists, logic_files);
    auto [player_deck, bot_deck, bot_logic_file] = selection.run();

    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    Rng rng(seed);
    SPDLOG_INFO("Game played with seed: {}", seed);

    GameGui gui(window, player_deck, bot_deck, *bot_logic_file, rng);
    gui.run();
}
