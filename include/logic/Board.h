#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "logic/Minion.h"

class Board
{
private:
    std::vector<Minion> board_;
public:
    static constexpr unsigned MAX_BOARD_SIZE = 7;

    Board();
    void add_minion(const Minion& minion, unsigned position);
    unsigned minion_count() const;
    Minion& get_minion(unsigned position);
    void remove_dead_minions();
};

#endif