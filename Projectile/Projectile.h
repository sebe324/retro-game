#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Unit.h"
#include "../enums/DamageType.h"
#include "../playerClasses/Player.h"
#include "../Monster.h"
#include "../particleSystem/particleSystem.h"
class Projectile : public Unit{

    public:
        float damage=0.f;
        sf::Time lifetime;
        DamageType damageType;
        bool destroyedOnImpact=true;
        Projectile(std::string n, float dmg, sf::Time lt, DamageType dmgtype, sf::Vector2f p, sf::Vector2f s, float spd);
        void update(sf::Time elapsed,std::vector<std::unique_ptr<Monster>> &monsters, std::unique_ptr<Player> &player, ParticleSystem &particleSystem);
};
#endif // PROJECTILE_H
