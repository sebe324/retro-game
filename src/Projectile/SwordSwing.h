#ifndef SWORDSWING_H
#define SWORDSWING_H

#include "Projectile.h"

class SwordSwing : public Projectile{
    public:
        SwordSwing(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);
};
#endif // SWORDSWING_H
