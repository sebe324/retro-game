#include "Rock.h"
#include "../core/Character.h"
Rock::Rock(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Rock", dmg, sf::seconds(2),PHYSIC,p,{80.f,80.f},dest,350.f,attackMons){
createBodyPart({80.f,80.f},{0.f,0.f},sf::Color{40,40,40});
disappearOnImpact=true;
rotate(atan2(velY,velX)*180/3.14);
}
void Rock::onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem){
    target.removeHealth(damage, EARTH, particleSystem);

    if(velocity.x != 0 && velocity.y != 0)
        target.velocity += velocity*15.f;
    else
        target.velocity += sf::Vector2f(30.f, 30.f);

    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter({hitbox.left,hitbox.top+25.f},10,{35,40},{35,40},{35,40});
}
