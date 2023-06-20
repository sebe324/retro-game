#ifndef FIREBALL_H
#define FIREBALL_H

#include "Projectile.h"

class FireBall: public Projectile{

public:

FireBall(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);
void onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem);
};
#endif
