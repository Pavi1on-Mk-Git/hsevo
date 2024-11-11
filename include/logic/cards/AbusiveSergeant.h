#ifndef ABUSIVE_SERGEANT_H
#define ABUSIVE_SERGEANT_H

#include "logic/cards/MinionCard.h"

class AbusiveSergeant: public MinionCard
{
private:
    AbusiveSergeant(): MinionCard("Abusive Sergeant", 1, 2, 1) {}
public:
    static const AbusiveSergeant instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const AbusiveSergeant AbusiveSergeant::instance;

#endif