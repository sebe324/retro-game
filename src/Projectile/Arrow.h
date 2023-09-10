#ifndef ARROW_H
#define ARROW_H

#include "Projectile.h"
class Arrow : public Projectile {
    public:
        Arrow(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);
};
#endif // ARROW_H
