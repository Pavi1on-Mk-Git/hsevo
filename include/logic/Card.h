#ifndef CARD_H
#define CARD_H

#include <functional>
#include <memory>
#include <string>

#include "logic/MinionKeywords.h"
#include "logic/PlayCardAction.h"

struct Card;

void default_on_play(Game& game, std::vector<OnPlayArg> args);
std::vector<std::unique_ptr<PlayCardAction>> default_create_play_actions(
    const std::unique_ptr<Card>& self, Game& game, unsigned hand_position
);

struct Card
{
    const std::string name;
    const unsigned base_health;
    unsigned mana_cost, attack;
    int health;

    const std::function<void(Game&, std::vector<OnPlayArg>)> on_play_func;
    const std::function<std::vector<std::unique_ptr<PlayCardAction>>(const std::unique_ptr<Card>&, Game&, unsigned)>
        create_play_actions_func;

    MinionKeywords keywords;

    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const std::function<void(Game&, std::vector<OnPlayArg>)>& on_play_func,
        const std::function<
            std::vector<std::unique_ptr<PlayCardAction>>(const std::unique_ptr<Card>&, Game&, unsigned)>&
            create_play_actions_func,
        const MinionKeywords& keywords = NO_KEYWORDS
    );

    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords = NO_KEYWORDS
    );
};

#endif
