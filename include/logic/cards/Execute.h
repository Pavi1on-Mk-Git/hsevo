#ifndef EXECUTE_H
#define EXECUTE_H

#include "logic/cards/Card.h"

class Execute: public Card
{
private:
    Execute(): Card("Execute", 1) {}
public:
    static const Execute instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const Execute Execute::instance;

#endif