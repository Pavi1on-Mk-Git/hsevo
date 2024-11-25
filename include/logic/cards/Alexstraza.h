#ifndef ALEXSTRAZA_H
#define ALEXSTRAZA_H

#include "logic/cards/MinionCard.h"

class Alexstraza: public MinionCard
{
private:
    Alexstraza(): MinionCard("Alexstraza", 9, 8, 8) {}
public:
    static const Alexstraza instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const Alexstraza Alexstraza::instance;

#endif