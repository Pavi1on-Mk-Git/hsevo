#include "logic/Board.h"

#include <algorithm>

Board::Board()
{
    board_.reserve(MAX_BOARD_SIZE);
}

void Board::add_minion(const Minion& minion, unsigned position)
{
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
    std::erase_if(board_, [](const Minion& minion) { return minion.health <= 0; });
}

void Board::trigger_end_of_turn()
{
    std::ranges::for_each(board_, [](Minion& minion) {
        if(minion.will_die_horribly)
            minion.health = 0;
    });
}

const MinionCard* Board::remove_minion(unsigned position)
{
    auto& to_remove = board_.at(position);
    const auto* card = to_remove.card;
    board_.erase(board_.begin() + position);
    return card;
}

std::vector<Minion>::iterator Board::begin()
{
    return board_.begin();
}

std::vector<Minion>::const_iterator Board::begin() const
{
    return board_.begin();
}

std::vector<Minion>::iterator Board::end()
{
    return board_.end();
}

std::vector<Minion>::const_iterator Board::end() const
{
    return board_.end();
}
