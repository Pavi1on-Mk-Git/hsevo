#ifndef HERO_H
#define HERO_H

#include <memory>

#include "logic/Entity.h"
#include "logic/HeroPowerAction.h"

class Hero: public Entity
{
private:
    unsigned fatigue_dmg_;
protected:
    Hero(
        std::string_view name, std::string_view hero_power_name, unsigned hero_power_mana_cost,
        const Tribe& tribe = Tribe::NONE
    );
public:
    std::string hero_power_name;
    unsigned hero_power_mana_cost;
    bool hero_power_active;

    virtual ~Hero() = default;
    virtual std::vector<Game> on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args) = 0;
    virtual std::vector<std::unique_ptr<HeroPowerAction>> create_hero_power_use_actions(const Game& game) = 0;
    virtual std::unique_ptr<Hero> clone() const = 0;
    void fatigue(unsigned count);
};

#define CLONE_HERO                                                                             \
std::unique_ptr<Hero> clone() const override                                                   \
{                                                                                              \
return std::make_unique<std::remove_const_t<std::remove_reference_t<decltype(*this)>>>(*this); \
}

#endif