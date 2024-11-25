#ifndef GAME_H
#define GAME_H

#include "ai/GameStateInput.h"
#include "logic/EndTurnAction.h"
#include "logic/FightAction.h"
#include "logic/HeroPowerAction.h"
#include "logic/PlayMinionAction.h"
#include "logic/PlaySpellAction.h"
#include "logic/Player.h"

enum class GameResult
{
    PLAYER_1,
    PLAYER_2,
    TIE,
};

class Game
{
private:
    unsigned active_player_;
    std::vector<unsigned> minion_ids_;
    std::vector<unsigned> play_order_;

    void mulligan();
    std::vector<std::unique_ptr<Action>> get_attack_actions() const;
    std::vector<Game> trigger_on_death() const;
    std::vector<Game> trigger_end_of_turn() const;

    HeroInput get_hero_state(unsigned player_index) const;
public:
    std::array<Player, 2> players;
    bool turn_ended;

    Game(const Decklist& first_decklist, const Decklist& second_decklist, bool reverse_player_order = false);
    std::optional<GameResult> check_winner() const;
    void switch_active_player();
    std::vector<std::unique_ptr<Action>> get_possible_actions() const;
    Player& current_player();
    Player& opponent();
    const Player& current_player() const;
    const Player& opponent() const;
    GameStateInput get_state() const;
    void draw(unsigned amount, unsigned player_id);
    void draw(unsigned amount = 1);
    unsigned next_minion_id();
    void add_minion(const MinionCard* card, unsigned position, unsigned player_id);
    void add_minion(const MinionCard* card, unsigned position, bool own_board = true);
    const MinionCard* bounce_minion(unsigned position);
    void change_minion_side(unsigned player_id, unsigned position);
    static std::vector<Game> do_fight_actions(std::vector<std::pair<Game, FightAction>>& states_and_actions);
    std::vector<Game> do_action(const EndTurnAction& action) const;
    std::vector<Game> do_action(const PlayMinionAction& action) const;
    std::vector<Game> do_action(const PlaySpellAction& action) const;
    std::vector<Game> do_action(const FightAction& action) const;
    std::vector<Game> do_action(const HeroPowerAction& action) const;
};

#endif