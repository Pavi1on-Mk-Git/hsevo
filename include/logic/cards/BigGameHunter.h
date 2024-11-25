#ifndef BIG_GAME_HUNTER_H
#define BIG_GAME_HUNTER_H

#include "logic/cards/MinionCard.h"

class BigGameHunter: public MinionCard
{
private:
    BigGameHunter(): MinionCard("Big Game Hunter", 3, 4, 2) {}
public:
    static const BigGameHunter instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const BigGameHunter BigGameHunter::instance;

#endif
