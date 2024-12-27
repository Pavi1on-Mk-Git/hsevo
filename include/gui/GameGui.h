#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <future>
#include <raylib-cpp.hpp>

#include "gui/GuiElement.h"
#include "logic/Game.h"
#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"

/**
 * Class which manages drawing a screen containg the game
 */
class GameGui

{
private:
    /**
     * Window in which the game will be drawn
     */
    raylib::Window& window_;

    /**
     * Flag signaling whether the bot will play first
     */
    const bool is_bot_first_;

    /**
     * Flag signaling if current game turn is already started
     */
    bool is_turn_started_;

    /**
     * Logic used by player and bot respectively
     */
    std::unique_ptr<const PlayerLogic> player_logic_, bot_logic_;

    /**
     * Game state
     */
    Game game_;

    /**
     * Winner of the played game
     */
    std::optional<GameResult> winner_;

    /**
     * Cuurent turn number
     */
    unsigned current_turn_;

    /**
     * Gui elements to draw
     */
    std::vector<std::unique_ptr<GuiElement>> elements_;

    /**
     * State resulting from bot's decision in its turn
     */
    std::future<Game> bot_action_result_;

    /**
     * Update the game state by playing actions selected using provided player logic
     */
    void update();

    /**
     * Update game state by advancing it to the next turn
     */
    void update_begin_turn();

    /**
     * Choose an action played by the bot with a slight delay
     */
    Game delayed_action();

    /**
     * Draw all gui elements present
     */
    void draw();
public:
    /**
     * Position of the gap into which a minion is about to be played
     * Used to inform the gui about how to properly offset drawing minions present on the board
     */
    std::optional<unsigned> minion_gap_position;

    /**
     * Flag signaling if the player is currently using a card with discover effect
     */
    bool is_in_discover_mode;

    /**
     * Construct a game gui
     * @param window Window in which the game will be drawn
     * @param player_deck Deck which will be used by the player
     * @param bot_deck Deck which will be used by the bot
     * @param bot_logic_file File containing the logic used by the bot
     * @param rng Source of randomness
     */
    GameGui(
        raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& bot_logic_file,
        Rng& rng
    );

    /**
     * Run the game
     * @return Winner of the game
     */
    GameResult run();

    /**
     * Return information about the current turn
     * @return true if it's player's turn, false otherwise
     */
    bool is_player_turn() const;

    /**
     * Scale a rectangle with dimensions represented by percentages to match the dimensions of the window
     * @param original Rectangle to scale
     * @return Scaled rectangle
     */
    raylib::Rectangle scale(const raylib::Rectangle& original) const;

    /**
     * Return id of the element which has been clicked by the user
     * @return Id of the clicked element
     */
    std::optional<GuiElementId> clicked_element() const;

    /**
     * Mark as active all elements whose ids match one of the potential sequences
     * @param potential_sequences Sequences to match against element ids
     */
    void make_active(const std::vector<std::deque<GuiElementId>> potential_sequences = {});
};

#endif