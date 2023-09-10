#ifndef ROCK_H
#define ROCK_H

class Character;

#include "Projectile.h"

class Rock : public Projectile{
    public:
        Rock(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);

    protected:
        void onImpact(sf::Time elapsed,Character& target, std::vector<ParticleSystem> &particleSystem);
};
#endif // ROCK_H
