#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "logic/Minion.h"

/**
 * Represents one side of a board used in the game
 */
class Board
{
private:
    /**
     * Underlying collection of minions
     */
    std::vector<Minion> board_;
public:
    /**
     * Maximum amount of minions possible to be on the board at the same time
     */
    static constexpr unsigned MAX_BOARD_SIZE = 7;

    /**
     * Construct an empty board
     */
    Board();

    /**
     * Add a minion to the board
     *
     * If the position exceeds maximum board size, no minion gets added
     * @param minion Minion to add
     * @param position Board position at which the minion will be added
     */
    void add_minion(const Minion& minion, unsigned position);

    /**
     * Transform a minion at `position` into `new_minion`
     * @param new_minion Minion to transform the selected one into
     * @param position Position of the selected minion
     */
    void transform_minion(const Minion& new_minion, unsigned position);

    /**
     * Return amount of minions present on the board
     * @return Minion count
     */
    unsigned minion_count() const;

    /**
     * Get the minion present at selected position
     * @param position Selected minion's position
     * @return Selected minion
     */
    Minion& get_minion(unsigned position);

    /**
     * Get the minion present at selected position (constant)
     * @param position Selected minion's position
     * @return Selected minion
     */
    const Minion& get_minion(unsigned position) const;

    /**
     * Remove all minions whose health is `<= 0` from the board
     */
    void remove_dead_minions();

    /**
     * Remove minion at selected position from the board
     * @param position Selected minion's position
     * @return Underlying card of the removed minion
     */
    const MinionCard* remove_minion(unsigned position);

    std::vector<Minion>::iterator begin();
    std::vector<Minion>::const_iterator begin() const;
    std::vector<Minion>::iterator end();
    std::vector<Minion>::const_iterator end() const;
};

#endif