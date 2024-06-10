#ifndef GAME_H
#define GAME_H

#include "AIPlayer.h"
#include "Deck.h"

class Game
{
private:
    std::ranlux24_base& _random_engine;
    std::array<AIPlayer, 2> _players;
    unsigned int _active_player;
    bool _game_ended;

    void switch_active_player();
    void mulligan();
    void do_turn();
    void draw(unsigned int amount);
    void draw();
public:
    Game(std::array<AIPlayer, 2> players, std::ranlux24_base& random_engine);
    void run();
};

#endif