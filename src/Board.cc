#include "Board.h"

#include <algorithm>

Board::Board()
{
    board_.reserve(MAX_BOARD_SIZE);
}

void Board::add_minion(const Minion& minion, unsigned position)
{
    board_.insert(board_.begin() + position, std::move(minion));
}

unsigned Board::minion_count()
{
    return board_.size();
}

Minion& Board::get_minion(unsigned position)
{
    return board_.at(position);
}

void Board::remove_dead_minions()
{
    auto new_end = std::remove_if(board_.begin(), board_.end(), [](const auto& minion) { return minion.health <= 0; });
    board_.erase(new_end, board_.end());
}