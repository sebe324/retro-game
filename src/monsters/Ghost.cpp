#include "Ghost.h"
#include "../Projectile/SpectralOrb.h"

Ghost::Ghost(sf::Vector2f p) : Monster("Ghost",1,5,p) {
    createBodyPart({50.f,80.f},{0.f,0.f},sf::Color(126,214,223));
    createBodyPart({5.f,5.f},{10.f,10.f},sf::Color(34,166,179));
    createBodyPart({5.f,5.f},{35.f,10.f},sf::Color(34,166,179));
    attitude=Neutral;
    defaultAttitude=Neutral;
    fightUntilDeath=true;
    bodyType=UNDEAD;
}

void Ghost::removeHealth(float n, DamageType damageType, std::vector<ParticleSystem> &particleSystem) {
    if (damageType==LIGHT || damageType==TRUE) {
        Character::removeHealth(n,damageType,particleSystem);
        return;
    }
    float t=Utils::randomize(1,100);
    if (t<50) {
        Character::removeHealth(n,damageType,particleSystem);
    }
    else {
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left,hitbox.top),"MISS",1,sf::Color(250,100,100),36);
    }
}

void Ghost::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed) {
    if (attackDelay-elapsed<sf::Time::Zero) {
        SpectralOrb spectralOrb(getCenter(),mousePos,damage,false);
        projectiles.push_back(std::make_unique<SpectralOrb>(spectralOrb));
        attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}
