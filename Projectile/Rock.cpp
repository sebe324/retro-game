#include "Rock.h"
#include "../Character.h"
Rock::Rock(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Rock", dmg, sf::seconds(2),PHYSIC,p,{80.f,80.f},dest,200.f,attackMons){
createBodyPart({80.f,80.f},{0.f,0.f},sf::Color{40,40,40});
disappearOnImpact=true;
rotate(atan2(velY,velX)*180/3.14);
}
void Rock::onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem){
    target.removeHealth(damage);
    target.velocity+=velocity*15.f;
    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter({hitbox.left,hitbox.top+25.f},10,{35,40},{35,40},{35,40});
}
