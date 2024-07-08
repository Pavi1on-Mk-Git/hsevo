#ifndef GAME_H
#define GAME_H

#include "EndTurnAction.h"
#include "GameStateInput.h"
#include "HitHeroAction.h"
#include "PlayCardAction.h"
#include "Player.h"
#include "TradeAction.h"

enum class GameResult
{
    PLAYER_1,
    PLAYER_2,
    TIE,
};

class Game
{
private:
    std::ranlux24_base& _random_engine;
    std::array<Player, 2> players_;
    unsigned int active_player_;
    bool game_ended_;
    GameResult winner_;
    bool turn_ended_;

    void check_winner();
    void switch_active_player();
    Player& current_player();
    Player& opponent();

    void mulligan();
    void do_turn();
    void draw(unsigned int amount);
    void draw();
    std::vector<std::unique_ptr<Action>> get_possible_actions();
    PlayerStateInput get_player_state(unsigned int player_index);
public:
    Game(
        const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player,
        std::ranlux24_base& random_engine
    );
    GameResult run();
    Game copy() const;
    GameStateInput get_state();
    void do_action(const EndTurnAction& action);
    void do_action(const PlayCardAction& action);
    void do_action(const TradeAction& action);
    void do_action(const HitHeroAction& action);
};

#endif