#ifndef GHOST_H
#define GHOST_H

#include "../Monster.h"

class Ghost : public Monster{
    public:
Ghost(sf::Vector2f p);
void removeHealth(float n, DamageType damageType, std::vector<ParticleSystem> &particleSystem);
};
#endif // GHOST_H
