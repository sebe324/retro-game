#include "Projectile.h"
#include "../playerClasses/Player.h"
#include "../monsters/Monster.h"
#include "../core/Character.h"

Projectile::Projectile(std::string n, float dmg, sf::Time lt, DamageType dmgtype, sf::Vector2f p, sf::Vector2f s, sf::Vector2f dest, float spd, bool attackMons) : Unit(n,p,s,spd) {
    damage=dmg;
    lifetime=lt;
    damageType=dmgtype;
    destination=dest;
    attackMonsters=attackMons;
    float dist=sqrt((destination.x-hitbox.left)*(destination.x-hitbox.left)+(destination.y-hitbox.top)*(destination.y-hitbox.top));
    velX=(destination.x-hitbox.left)/dist;
    velY=(destination.y-hitbox.top)/dist;
}

void Projectile::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>> &monsters, std::unique_ptr<Player> &player, std::vector<ParticleSystem> &particleSystem) {
    lifetime-=elapsed;
    if (lifetime>=sf::Time::Zero) {
        if (dealDamage) {
            if (attackMonsters) {
                for (int i=monsters.size(); i>0; i--) {
                    if (hitbox.intersects(monsters[i-1]->hitbox)) {
                        if (!checkIfMonsterWasHit(monsters[i-1])) {
                            onImpact(elapsed, *monsters[i-1], particleSystem);
                            if (disappearOnImpact) lifetime=sf::Time::Zero;
                            if (monsters[i-1]->attitude==Neutral) monsters[i-1]->attitude=Aggressive;
                            if (monsters[i-1]->getHealth()<=0) {
                                monstersHit.erase(std::remove(monstersHit.begin(), monstersHit.end(), monsters[i-1]->getId()), monstersHit.end());
                            }
                            if (stopDealingDamageOnImpact) dealDamage=false;
                            break;
                        }
                    }
                }
            }
            else {
                if (hitbox.intersects(player->hitbox) && !playerHit) {
                    onImpact(elapsed, *player, particleSystem);
                    playerHit=true;
                    if (disappearOnImpact) lifetime=sf::Time::Zero;
                    if (stopDealingDamageOnImpact) dealDamage=false;
                }
            }
            velocity.y=elapsed.asSeconds()*velY*speed;
            velocity.x=elapsed.asSeconds()*velX*speed;
            move();
        }
    }
}

bool Projectile::checkIfMonsterWasHit(std::unique_ptr<Monster> &monster) {
    for (int i=0; i<monstersHit.size(); i++) {
        if (monster->getId()==monstersHit[i]) {
            return true;
        }
    }
    monstersHit.push_back(monster->getId());
    return false;
}

void Projectile::onImpact(sf::Time elapsed,Character& target, std::vector<ParticleSystem> &particleSystem) {
    target.removeHealth(damage, damageType, particleSystem);
}


