#include "Zombie.h"

Zombie::Zombie(sf::Vector2f p) : Monster("Zombie",2,8,p){
    createBodyPart({25.f,15.f},{12.5f,0.f},sf::Color(253,167,223));
    createBodyPart({30.f,20.f},{10.f,5.f},sf::Color(0,148,50));
    createBodyPart({5.f,5.f},{10.f,10.f},sf::Color(100,20,20));
    createBodyPart({5.f,5.f},{20.f,10.f},sf::Color(100,20,20));
    createBodyPart({30.f,40.f},{10.f,25.f},sf::Color(6,82,221));
    createBodyPart({10.f,30.f},{0.f,25.f},sf::Color(0,148,50));
    createBodyPart({10.f,30.f},{40.f,25.f},sf::Color(0,148,50));
    createBodyPart({15.f,10.f},{5.f,65.f},sf::Color(50,50,50));
    createBodyPart({15.f,10.f},{30.f,65.f},sf::Color(50,50,50));
    attitude=Aggressive;
    defaultAttitude=Aggressive;
    fightUntilDeath=true;
    bodyType=UNDEAD;
}

Zombie::Zombie() : Monster(){}

void Zombie::wakeUp(){
    asleep=false;
/*bodyParts[2].setPosition(hitbox.left+20.f,hitbox.top+10.f);
bodyParts[3].setPosition(hitbox.left+30.f,hitbox.top+10.f);
bodyParts[2].setSize({5.f,5.f});
bodyParts[3].setSize({5.f,5.f});*/
}

void Zombie::goSleep(){
    asleep=true;
/*bodyParts[2].setPosition(hitbox.left+20.f,hitbox.top+13.f);
bodyParts[3].setPosition(hitbox.left+30.f,hitbox.top+13.f);
bodyParts[2].setSize({5.f,2.f});
bodyParts[3].setSize({5.f,2.f});*/
}
