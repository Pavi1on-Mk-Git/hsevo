#ifndef GAME_H
#define GAME_H

#include "ai/GameStateInput.h"
#include "logic/EndTurnAction.h"
#include "logic/HitHeroAction.h"
#include "logic/PlayCardAction.h"
#include "logic/Player.h"
#include "logic/TradeAction.h"

enum class GameResult
{
    PLAYER_1,
    PLAYER_2,
    TIE,
};

class Game
{
private:
    std::array<Player, 2> players_;
    unsigned active_player_;
    bool game_ended_;
    GameResult winner_;
    bool turn_ended_;

    void check_winner();
    void switch_active_player();

    void mulligan();
    void do_turn();
    void draw(unsigned amount);
    void draw();
    std::vector<std::unique_ptr<Action>> get_possible_actions();
    std::vector<std::unique_ptr<Action>> get_attack_actions();
    PlayerStateInput get_player_state(unsigned player_index);
public:
    Game(const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player);
    GameResult run();
    Game copy() const;
    Player& current_player();
    Player& opponent();
    const Player& current_player() const;
    const Player& opponent() const;
    GameStateInput get_state();
    void do_action(const EndTurnAction& action);
    void do_action(const PlayCardAction& action);
    void do_action(const TradeAction& action);
    void do_action(const HitHeroAction& action);
};

#endif