#include "SpectralOrb.h"
#include "../Utilities/Utils.h"
SpectralOrb::SpectralOrb(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Spectral Orb", dmg, sf::seconds(.5),DARKNESS,p,{40.f,60.f},dest,500.f,attackMons)
{
    createBodyPart({Utils::randomize(10,40),Utils::randomize(10,40)},{0.f,0.f},sf::Color{40,120,120});

    rotate(atan2(velY,velX)*180/3.14);
}
