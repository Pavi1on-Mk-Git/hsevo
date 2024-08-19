#ifndef CARD_H
#define CARD_H

#include <functional>
#include <memory>
#include <string>

#include "logic/MinionKeywords.h"
#include "logic/PlayCardAction.h"

struct Card;

unsigned default_mana_cost(const Card& self, const Game& game);
void default_on_play(Game& game, std::vector<OnPlayArg> args);
std::vector<std::unique_ptr<PlayCardAction>> default_create_play_actions(
    const Card& self, const Game& game, unsigned hand_position
);

struct Card
{
    const std::string name;
    const unsigned mana_cost_, base_health;
    unsigned attack;
    int health;

    const std::function<unsigned(const Card&, const Game&)> mana_cost;
    const std::function<void(Game&, std::vector<OnPlayArg>)> on_play;
    const std::function<std::vector<std::unique_ptr<PlayCardAction>>(const Card&, const Game&, unsigned)>
        create_play_actions;

    MinionKeywords keywords;

    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const std::function<void(Game&, std::vector<OnPlayArg>)>& on_play,
        const std::function<std::vector<std::unique_ptr<PlayCardAction>>(const Card&, const Game&, unsigned)>&
            create_play_actions,
        const MinionKeywords& keywords = NO_KEYWORDS
    );

    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords = NO_KEYWORDS
    );

    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const std::function<unsigned(const Card&, const Game&)> mana_cost, const MinionKeywords& keywords = NO_KEYWORDS
    );
};

#endif
