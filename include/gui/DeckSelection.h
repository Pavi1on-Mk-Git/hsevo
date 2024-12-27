#ifndef DECK_SELECTION_H
#define DECK_SELECTION_H

#include <raylib-cpp.hpp>

#include "logic/Decklist.h"

/**
 * Class which manages drawing a screen containing selection of decks to choose from
 */
class DeckSelection
{
private:
    /**
     * Window in which the screen will be drawn
     */
    raylib::Window& window_;

    /**
     * Decklists to choose from
     */
    std::vector<const Decklist*> decklists_;

    /**
     * Files containing logics of bots the player can play against
     */
    std::vector<std::ifstream*> logic_files_;

    /**
     * Deck chosen for the player
     */
    const Decklist* player_deck_;

    /**
     * Deck chosen for the bot
     */
    const Decklist* bot_deck_;

    /**
     * File containing the logic of the chosen bot
     */
    std::ifstream* bot_logic_file_;

    /**
     * Buttons used for deck selection
     */
    std::vector<raylib::Rectangle> deck_choice_buttons_;

    /**
     * Information about deck selection button highlight status
     */
    std::vector<bool> button_is_highlighted;

    /**
     * Handles user input and saves information about decklists player has selected / is hovering mouse over
     */
    void update();

    /**
     * Draws current state of the deck selection screen
     */
    void draw();
public:
    /**
     * Construct a deck selection screen
     * @param window Window to draw the screen in
     * @param decklists Decklists the player may choose from
     * @param logic_files Bot logic files associated with provided decklists
     */
    DeckSelection(
        raylib::Window& window, const std::vector<const Decklist*>& decklists,
        const std::vector<std::ifstream*>& logic_files
    );

    /**
     * Run the deck selection process
     * @return A tuple of chosen player deck, bot deck and bot logic in that order
     */
    std::tuple<const Decklist*, const Decklist*, std::ifstream*> run();
};

#endif