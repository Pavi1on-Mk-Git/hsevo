#ifndef MISDIRECTION_H
#define MISDIRECTION_H

#include "logic/cards/SecretCard.h"

class Misdirection: public SecretCard
{
private:
    Misdirection(): SecretCard("Misdirection", 2) {}
public:
    static const Misdirection instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    SecretResult on_trigger(const Game& prev_state, const FightAction& action) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const Misdirection Misdirection::instance;

#endif