#include "Projectile.h"
#include "../playerClasses/Player.h"
#include "../Monster.h"
Projectile::Projectile(std::string n, float dmg, sf::Time lt, DamageType dmgtype, sf::Vector2f p, sf::Vector2f s, sf::Vector2f dest, float spd, bool attackMons) : Unit(n,p,s,spd){
damage=dmg;
lifetime=lt;
damageType=dmgtype;
destination=dest;
attackMonsters=attackMons;
float dist=sqrt((destination.x-hitbox.left)*(destination.x-hitbox.left)+(destination.y-hitbox.top)*(destination.y-hitbox.top));
std::cout<<dist<<std::endl;
velX=(destination.x-hitbox.left)/dist;
velY=(destination.y-hitbox.top)/dist;
test=velY;;
if(destination.x-hitbox.left<0) test=-velY;
}

void Projectile::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>> &monsters, std::unique_ptr<Player> &player, std::vector<ParticleSystem> &particleSystem){
    lifetime-=elapsed;
    if(lifetime>=sf::Time::Zero){
        if(dealDamage){
        if(attackMonsters){
        for(int i=monsters.size(); i>0; i--){
            if(hitbox.intersects(monsters[i-1]->hitbox)){
                if(!checkIfMonsterWasHit(monsters[i-1])){
                monsters[i-1]->removeHealth(damage);
                particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i-1]->hitbox.left,monsters[i-1]->hitbox.top),Utils::toString(damage,1),1,sf::Color::White,36);
                std::cout<<&monsters[i-1]<<std::endl;
                if(disappearOnImpact) lifetime=sf::Time::Zero;
                if(monsters[i-1]->getHealth()<=0){
                    monstersHit.erase(std::remove(monstersHit.begin(), monstersHit.end(), &monsters[i-1]), monstersHit.end());
                    player->addExp(3*monsters[i-1]->getLevel());
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(monsters[i-1]->bodyParts,monsters[i-1]->bodyPartsNumber);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(monsters[i-1]->getCenter(),"+"+Utils::toString(monsters[i-1]->getLevel()*3)+"xp",1,sf::Color::Yellow,40);
                    monsters.erase(monsters.begin()+i-1);
                }
                if(stopDealingDamageOnImpact) dealDamage=false;
                break;
            }
            }
        }

        }
        else{
            if(hitbox.intersects(player->hitbox) && !playerHit){
                player->removeHealth(damage);
                particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(player->getCenter(),Utils::toString(damage,1),1,sf::Color::Red,36);
                playerHit=true;
                if(disappearOnImpact) lifetime=sf::Time::Zero;
                if(stopDealingDamageOnImpact) dealDamage=false;
            }
        }
    velocity.y=elapsed.asSeconds()*velY*250;
    velocity.x=elapsed.asSeconds()*velX*250;
    move();
    }
    }
}

bool Projectile::checkIfMonsterWasHit(std::unique_ptr<Monster> &monster){
for(int i=0; i<monstersHit.size(); i++){
    if(&monster==monstersHit[i]){
            return true;
    }
}
monstersHit.push_back(&monster);
return false;
}


