#ifndef FIREBLAZE_H
#define FIREBLAZE_H

#include "Ability.h"

class FireBlaze : public Ability{
    public:
    FireBlaze();
    bool effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles);
};
#endif // HEAL_H

