#ifndef GAME_H
#define GAME_H

#include "ai/GameStateInput.h"
#include "logic/EndTurnAction.h"
#include "logic/HeroHitHeroAction.h"
#include "logic/HeroPowerAction.h"
#include "logic/HeroTradeAction.h"
#include "logic/HitHeroAction.h"
#include "logic/PlayMinionAction.h"
#include "logic/PlaySpellAction.h"
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
    std::vector<std::unique_ptr<Action>> get_possible_actions() const;
    std::vector<std::unique_ptr<Action>> get_attack_actions() const;
    HeroInput get_hero_state(unsigned player_index) const;
public:
    Game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player);
    Player& current_player();
    Player& opponent();
    const Player& current_player() const;
    const Player& opponent() const;
    GameStateInput get_state() const;
    void draw(unsigned amount);
    void draw();
    std::vector<Game> do_action(const EndTurnAction& action);
    std::vector<Game> do_action(const PlayMinionAction& action);
    std::vector<Game> do_action(const PlaySpellAction& action);
    std::vector<Game> do_action(const TradeAction& action);
    std::vector<Game> do_action(const HitHeroAction& action);
    std::vector<Game> do_action(const HeroPowerAction& action);
    std::vector<Game> do_action(const HeroTradeAction& action);
    std::vector<Game> do_action(const HeroHitHeroAction& action);

    friend GameResult run_game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player);
    friend void do_turn(Game& game);
};

#endif