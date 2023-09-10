#ifndef SPECTRALORB_H
#define SPECTRALORB_H

#include "Projectile.h"

class SpectralOrb : public Projectile
{
    public:
        SpectralOrb(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons);
};
#endif // SPECTRALORB_H
