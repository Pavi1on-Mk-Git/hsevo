#include "logic/Board.h"

#include <algorithm>

Board::Board()
{
    board_.reserve(MAX_BOARD_SIZE);
}

void Board::add_minion(const Minion& minion, unsigned position)
{
    if(minion_count() < MAX_BOARD_SIZE)
        board_.insert(board_.begin() + position, minion);
}

void Board::transform_minion(const Minion& new_minion, unsigned position)
{
    board_.at(position) = new_minion;
}

unsigned Board::minion_count() const
{
    return board_.size();
}

Minion& Board::get_minion(unsigned position)
{
    return board_.at(position);
}

const Minion& Board::get_minion(unsigned position) const
{
    return board_.at(position);
}

void Board::remove_dead_minions()
{
    auto new_end = std::remove_if(board_.begin(), board_.end(), [](const Minion& minion) {
        return minion.health <= 0;
    });
    board_.erase(new_end, board_.end());
}

void Board::trigger_end_of_turn()
{
    auto new_end = std::remove_if(board_.begin(), board_.end(), [](const Minion& minion) {
        return minion.will_die_horribly;
    });
    board_.erase(new_end, board_.end());
}