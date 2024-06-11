#ifndef GAME_H
#define GAME_H

#include <optional>

#include "AIPlayer.h"
#include "Deck.h"
#include "EndTurnAction.h"
#include "HitHeroAction.h"
#include "PlayCardAction.h"
#include "TradeAction.h"

class Game
{
private:
    std::ranlux24_base& _random_engine;
    std::array<AIPlayer, 2> _players;
    unsigned int _active_player;
    bool _game_ended;
    std::optional<unsigned int> _winner;
    bool _turn_ended;

    void check_winner();
    void switch_active_player();
    AIPlayer& current_player();
    AIPlayer& opponent();

    void mulligan();
    void do_turn();
    void draw(unsigned int amount);
    void draw();
    std::vector<std::unique_ptr<Action>> get_possible_actions();
public:
    Game(std::array<AIPlayer, 2> players, std::ranlux24_base& random_engine);
    std::optional<unsigned int> run();
    void do_action(const EndTurnAction& action);
    void do_action(const PlayCardAction& action);
    void do_action(const TradeAction& action);
    void do_action(const HitHeroAction& action);
};

#endif