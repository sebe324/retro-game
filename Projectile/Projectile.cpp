#include "Projectile.h"

Projectile::Projectile(std::string n, float dmg, sf::Time lt, DamageType dmgtype, sf::Vector2f p, sf::Vector2f s, float spd) : Unit(n,p,s,spd){
damage=dmg;
lifetime=lt;
damageType=dmgtype;
}

void Projectile::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>> &monsters, std::unique_ptr<Player> &player, ParticleSystem& particles){
    lifetime-=elapsed;
    if(lifetime>=sf::Time::Zero){
        for(int i=0; i<monsters.size(); i++){
            if(hitbox.intersects(monsters[i]->hitbox)){
                monsters[i]->removeHealth(damage);
                particles.addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(damage),1,sf::Color::White,36);
                if(destroyedOnImpact) break;
                else continue;
            }
        }
    }
}
