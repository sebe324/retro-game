#include "Trap.h"
#include "../enums/ParticlesGame.h"

#include "../Unit.h"
#include "../Character.h"
Trap::Trap(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Trap", dmg, sf::seconds(10),PHYSIC,p,{40.f,60.f},dest,0.f,attackMons)
{
createBodyPart({50.f,10.f},{0.f,0.f},sf::Color(100,100,100));
createBodyPart({10.f,50.f},{40.f,0.f},sf::Color(100,100,100));
createBodyPart({10.f,50.f},{0.f,0.f},sf::Color(100,100,100));
createBodyPart({50.f,10.f},{0.f,40.f},sf::Color(100,100,100));

disappearOnImpact=true;
}

void Trap::onImpact(sf::Time elapsed, Character& target, std::vector<ParticleSystem> &particleSystem)
{
    particleSystem[PARTICLES_WORLD].addEmitter(getCenter(),10,{100,110},{100,110},{100,130});
    target.removeHealth(damage,damageType,particleSystem);
    target.speed=10.f;
}
