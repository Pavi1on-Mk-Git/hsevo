#ifndef CARD_H
#define CARD_H

#include <memory>
#include <string>

#include "logic/MinionKeywords.h"
#include "logic/PlayCardAction.h"

class Card
{
protected:
    const unsigned mana_cost_;
    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords = NO_KEYWORDS
    );
public:
    const std::string name;
    const unsigned base_attack, base_health;
    MinionKeywords keywords;

    virtual ~Card() = default;
    virtual unsigned mana_cost(const Game& game) const;
    virtual void on_play(Game& game, std::vector<OnPlayArg> args);
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position);
    virtual std::unique_ptr<Card> clone() const = 0;
};

#define CLONE                                                                                  \
std::unique_ptr<Card> clone() const override                                                   \
{                                                                                              \
return std::make_unique<std::remove_const_t<std::remove_reference_t<decltype(*this)>>>(*this); \
}

#endif
