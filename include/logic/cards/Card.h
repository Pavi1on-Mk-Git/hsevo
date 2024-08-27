#ifndef CARD_H
#define CARD_H

#include <memory>
#include <string>

#include "logic/PlayCardAction.h"

class Card
{
protected:
    const unsigned mana_cost_;
    Card(std::string_view name, unsigned base_cost);
public:
    const std::string name;

    virtual ~Card() = default;
    virtual unsigned mana_cost(const Game& game) const;
    virtual void on_play(Game& game, std::vector<OnPlayArg> args);
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(
        const Game& game, unsigned hand_position
    ) = 0;
    virtual std::unique_ptr<Card> clone() const = 0;
};

#define CLONE                                                                                  \
std::unique_ptr<Card> clone() const override                                                   \
{                                                                                              \
return std::make_unique<std::remove_const_t<std::remove_reference_t<decltype(*this)>>>(*this); \
}

#endif