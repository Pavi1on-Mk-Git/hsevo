#ifndef GUI_PLAYER_LOGIC_H
#define GUI_PLAYER_LOGIC_H

#include "players/PlayerLogic.h"
#include "utils/GuiElementId.h"
#include "utils/Rng.h"

struct GameGui;

/**
 * Player logic used for choosing actions for human player in gui
 */
class GuiPlayerLogic: public PlayerLogic
{
private:
    /**
     * Game gui used for the game being played
     */
    GameGui& gui_;

    /**
     * Source of randomness
     */
    Rng& rng_;

    /**
     * Sequence of elements clicked by the user since last chosen action
     */
    mutable std::deque<GuiElementId> click_sequence_;
public:
    /**
     * Construct a player logic using provided parameters
     * @param decklist Decklist used by the player
     * @param rng Source of randomness
     */
    GuiPlayerLogic(const Decklist& decklist, GameGui& gui, Rng& rng);
    Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions) const override;
};

#endif