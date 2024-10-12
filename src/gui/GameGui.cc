#include "gui/GameGui.h"

#include <raylib.h>
#include <tuple>

void GameGui::update() {}

void GameGui::draw()
{
    window_.BeginDrawing();

    window_.ClearBackground(RAYWHITE);

    raylib::Text text("Game Gui is being drawn", 40.f, BLACK, GetFontDefault(), 1.f);

    auto [width, height] = window_.GetSize();
    auto [x, y] = text.MeasureEx();
    text.Draw((width - x) / 2, (height - y) / 2);

    window_.EndDrawing();
}

static unsigned base_width = 1280;
static unsigned base_size = 720;
static unsigned fps = 60;

GameGui::GameGui(): window_(base_width, base_size, "hsevo")
{
    window_.SetTargetFPS(fps);
}

void GameGui::run()
{
    while(!window_.ShouldClose())
    {
        update();
        draw();
    }
}