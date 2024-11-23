#ifndef HERO_H
#define HERO_H

#include <memory>
#include <optional>

#include "logic/Entity.h"
#include "logic/HeroPowerAction.h"
#include "logic/Weapon.h"

class Hero: public Entity
{
private:
    unsigned fatigue_dmg_;
protected:
    Hero(
        const char* name, const char* hero_power_name, unsigned hero_power_mana_cost, unsigned base_health,
        const Tribe& tribe = Tribe::NONE
    );
public:
    const char* hero_power_name;
    unsigned hero_power_mana_cost;
    bool hero_power_active;

    bool active;
    std::optional<Weapon> weapon;
    unsigned armour;

    virtual ~Hero() = default;

    void restore_health(unsigned amount) override;
    void deal_dmg(unsigned amount, Game& game) override;
    virtual void on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args) = 0;
    virtual std::vector<std::unique_ptr<HeroPowerAction>> create_hero_power_use_actions(const Game& game);
    virtual std::unique_ptr<Hero> clone() const = 0;
    void fatigue(unsigned count);
};

#endif