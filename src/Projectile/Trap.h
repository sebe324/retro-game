#ifndef TRAP_H
#define TRAP_H

#include "Projectile.h"

class Character;
class Trap : public Projectile{
    public:
        Trap(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);

        void onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem);
};
#endif // TRAP_H
