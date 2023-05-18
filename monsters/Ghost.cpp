#include "Ghost.h"

Ghost::Ghost(sf::Vector2f p) : Monster("Ghost",1,5,p){
createBodyPart({50.f,80.f},{0.f,0.f},sf::Color(126,214,223));
createBodyPart({5.f,5.f},{10.f,10.f},sf::Color(34,166,179));
createBodyPart({5.f,5.f},{35.f,10.f},sf::Color(34,166,179));
attitude=Neutral;
defaultAttitude=Neutral;
fightUntilDeath=true;
bodyType=UNDEAD;
}

void Ghost::removeHealth(float n, DamageType damageType, std::vector<ParticleSystem> &particleSystem){
if(damageType==LIGHT || damageType==TRUE){
setHealth(getHealth()-n);
particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left,hitbox.top),Utils::toString(n,1),1,sf::Color::White,36);
}
else{
    float t=Utils::randomize(1,100);
    if(t<50){
        setHealth(getHealth()-n);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left,hitbox.top),Utils::toString(n,1),1,sf::Color::White,36);
    }
    else{
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left,hitbox.top),"MISS",1,sf::Color(250,100,100),36);
    }
}
}
