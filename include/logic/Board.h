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
    void transform_minion(const Minion& new_minion, unsigned position);
    unsigned minion_count() const;
    Minion& get_minion(unsigned position);
    const Minion& get_minion(unsigned position) const;
    void remove_dead_minions();
    void trigger_end_of_turn();
};

#endif