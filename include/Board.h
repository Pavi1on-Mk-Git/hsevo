#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "Minion.h"

class Board
{
private:
    std::vector<Minion> board_;
public:
    static constexpr unsigned int MAX_BOARD_SIZE = 7;

    Board();
    void add_minion(const Minion& minion, unsigned int position);
    unsigned int minion_count();
    Minion& get_minion(unsigned int position);
    void remove_dead_minions();
};

#endif