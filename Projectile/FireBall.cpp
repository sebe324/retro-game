#include "FireBall.h"
#include "../Character.h"

FireBall::FireBall(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons)
 : Projectile("FireBall", dmg, sf::seconds(5),MAGIC,p,{20.f,20.f},dest,300.f,attackMons){

createBodyPart({20.f,20.f},{-20.f,5.f},sf::Color(200,50,50));
createBodyPart({30.f,30.f},{0.f,0.f},sf::Color(200,50,50));
createBodyPart({20.f,20.f},{5.f,5.f},sf::Color(200,150,50));

disappearOnImpact=true;

rotate(atan2(velY,velX)*180/3.14);
}

void FireBall::onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem){
    target.removeHealth(damage);
    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter({hitbox.left,hitbox.top+25.f},10,{120,200},{10,40},{10,40});
}
