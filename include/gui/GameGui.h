#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <raylib-cpp.hpp>

class GameGui
{
private:
    raylib::Window window_;

    void update();
    void draw();
public:
    GameGui();
    void run();
};

#endif