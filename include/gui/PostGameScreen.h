#ifndef POST_GAME_SCREEN_H
#define POST_GAME_SCREEN_H

#include <raylib-cpp.hpp>

#include "gui/GameGui.h"

class PostGameScreen
{
private:
    /**
     * Window in which the screen will be drawn
     */
    raylib::Window& window_;

    /**
     * Text to display on the screen
     */
    const char* text_;

    /**
     * Draws text based on the result of the game
     */
    void draw() const;
public:
    /**
     * Construct a post game screen
     * @param window Window to draw the screen in
     * @param result Result of the game
     */
    PostGameScreen(raylib::Window& window, const BotGameResult& result);

    /**
     * Show the post game screen
     */
    void run() const;
};

#endif