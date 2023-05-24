#ifndef GHOST_H
#define GHOST_H

#include "../Monster.h"

class Ghost : public Monster{
    public:
Ghost(sf::Vector2f p);
void removeHealth(float n, DamageType damageType, std::vector<ParticleSystem> &particleSystem);
void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);
};
#endif // GHOST_H
