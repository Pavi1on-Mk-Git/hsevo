#ifndef TRACKING_H
#define TRACKING_H

#include "logic/cards/Card.h"

class Tracking: public Card
{
private:
    Tracking(): Card("Tracking", 1) {}
public:
    static const Tracking instance;
    static constexpr unsigned CHOICES = 3;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
    static unsigned amount_to_choose_from(const Game& game);
};

inline const Tracking Tracking::instance;

#endif