#ifndef CARD_H
#define CARD_H

#include <memory>

#include "logic/PlayCardAction.h"

class Card
{
protected:
    const unsigned mana_cost_;
    Card(const char* name, unsigned base_cost);
public:
    const char* name;

    virtual ~Card() = default;
    virtual unsigned mana_cost(const Game& game) const;
    virtual std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const;
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const;
};

#endif