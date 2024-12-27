#ifndef GAME_H
#define GAME_H

#include "ai/GameStateInput.h"
#include "logic/EndTurnAction.h"
#include "logic/FightAction.h"
#include "logic/HeroPowerAction.h"
#include "logic/PlayMinionAction.h"
#include "logic/PlaySpellAction.h"
#include "logic/Player.h"

/**
 * Result of a game
 */
enum class GameResult
{
    PLAYER_1,
    PLAYER_2,
    TIE,
};

/**
 * Game state
 */
class Game
{
private:
    /**
     * Currently active player
     */
    unsigned active_player_;

    /**
     * Ids of minions free to be used by new minions
     */
    std::vector<unsigned> minion_ids_;

    /**
     * Ids of minions in the order in which they appeared on the board
     */
    std::vector<unsigned> play_order_;

    /**
     * Draw 3 cards for the first player and 4 for the second. The player who goes second additionally receives The Coin
     * - a 0 mana spell which grants 1 mana on use
     */
    void mulligan();

    /**
     * Return all possible actions that involve attacking with an entity which can be taken in the current game state
     * @return Vector of actions
     */
    std::vector<std::unique_ptr<Action>> get_attack_actions() const;

    /**
     * Activate deathrattle effects for all the minions who have died
     * @return Resulting game states
     */
    std::vector<Game> trigger_on_death() const;

    /**
     * Activate end-of-turn effects for all the minions on board
     * @return Resulting game states
     */
    std::vector<Game> trigger_end_of_turn() const;

    /**
     * Get current state of the selected player
     * @param player_index Id of the selected player
     * @return Relevant state of the selected player
     */
    PlayerInput get_player_state(unsigned player_index) const;
public:
    /**
     * Players present in the game
     */
    std::array<Player, 2> players;

    /**
     * Flag signaling if the current player's turn has ended
     */
    bool turn_ended;

    /**
     * Construct a game using specified decklists
     * @param first_decklist First player decklist
     * @param second_decklist Second player decklist
     * @param rng Source of randomness
     * @param reverse_player_order If true first player will start second
     */
    Game(const Decklist& first_decklist, const Decklist& second_decklist, Rng& rng, bool reverse_player_order = false);

    /**
     * Check if the game has a winner
     * @return Game result if the game has ended, `std::nullopt` otherwise
     */
    std::optional<GameResult> check_winner() const;

    /**
     * Switch the currently active player
     */
    void switch_active_player();

    /**
     * Return all actions which can be taken by a player in current game state
     * @return Vector of actions
     */
    std::vector<std::unique_ptr<Action>> get_possible_actions() const;

    /**
     * Return currently active player
     * @return Active player
     */
    Player& current_player();

    /**
     * Return currently inactive player
     * @return Inactive player
     */
    Player& opponent();

    /**
     * Return currently active player
     * @return Active player
     */
    const Player& current_player() const;

    /**
     * Return currently inactive player
     * @return Inactive player
     */
    const Player& opponent() const;

    /**
     * Get current game state
     * @return Relevant state of the game
     */
    GameStateInput get_state() const;

    /**
     * Draw selected amount of cards from player's deck
     * @param amount Amount of cards to draw
     * @param plater_id Id of the player who will draw the cards
     */
    void draw(unsigned amount, unsigned player_id);

    /**
     * Draw selected amount of cards from currently active player's deck
     * @param amount Amount of cards to draw
     */
    void draw(unsigned amount = 1);

    /**
     * Return an id for the next minion which will be summoned
     * @return Id of the new minion
     */
    unsigned next_minion_id();

    /**
     * Add minion specified in the provided card to the player
     * @param card Minion card
     * @param position Position at which the minion will be added
     * @param player_id If of the player who will get the minion
     */
    void add_minion(const MinionCard* card, unsigned position, unsigned player_id);

    /**
     * Add minion specified in the provided card to a player
     * @param card Minion card
     * @param position Position at which the minion will be added
     * @param own_board If true - add the minion to current player's board, if false - opponent's
     */
    void add_minion(const MinionCard* card, unsigned position, bool own_board = true);

    /**
     * Return a selected minion back to its owner's hand
     * @param position Position of the minion
     * @return Underlying card of the returned minion
     */
    const MinionCard* bounce_minion(unsigned position);

    /**
     * Remove selected minion from the selected player's board and add it to the opposing player
     * @param player_id Id of the minion's player
     * @param position Position of the minion
     */
    void change_minion_side(unsigned player_id, unsigned position);

    /**
     * Calculate states resulting from applying provided fight actions to accompanying states
     * @param states_and_actions Vector of game states with actions to apply to them
     * @return Vector of resulting game states
     */
    static std::vector<Game> do_fight_actions(std::vector<std::pair<Game, FightAction>>& states_and_actions);

    /**
     * End the current turn
     * @param action Selected action
     * @return Vector of resulting game states
     */
    std::vector<Game> do_action(const EndTurnAction& action) const;

    /**
     * Play a minion card from hand
     * @param action Selected action
     * @return Vector of resulting game states
     */
    std::vector<Game> do_action(const PlayMinionAction& action) const;

    /**
     * Play a non-minion card from hand
     * @param action Selected action
     * @return Vector of resulting game states
     */
    std::vector<Game> do_action(const PlaySpellAction& action) const;

    /**
     * Initiate a fight between two entities present on the board
     * @param action Selected action
     * @return Vector of resulting game states
     */
    std::vector<Game> do_action(const FightAction& action) const;

    /**
     * Use current player's hero power
     * @param action Selected action
     * @return Vector of resulting game states
     */
    std::vector<Game> do_action(const HeroPowerAction& action) const;
};

#endif