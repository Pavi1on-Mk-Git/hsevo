#include "Board.h"

#include <algorithm>

Board::Board()
{
    board_.reserve(MAX_BOARD_SIZE);
}

void Board::add_minion(const Minion& minion, unsigned int position)
{
    board_.insert(board_.begin() + position, std::move(minion));
}

unsigned int Board::minion_count()
{
    return board_.size();
}

Minion& Board::get_minion(unsigned int position)
{
    return board_.at(position);
}

void Board::remove_dead_minions()
{
    auto new_end = std::remove_if(board_.begin(), board_.end(), [](const auto& minion) { return minion.health <= 0; });
    board_.erase(new_end, board_.end());
}