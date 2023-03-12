#ifndef GIANT_H
#define GIANT_H

#include "../Monster.h"
#include "../Projectile/Rock.h"
class Giant : public Monster{
    public:
Giant(sf::Vector2f p);
void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);
};
#endif // GIANT_H
