#ifndef HEAL_H
#define HEAL_H

#include "Ability.h"
#include "../particleSystem/particleSystem.h"
class Heal : public Ability{
    public:
    Heal();
    bool effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles);
};
#endif // HEAL_H
