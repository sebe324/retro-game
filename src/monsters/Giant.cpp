#include "Giant.h"

Giant::Giant(sf::Vector2f p) : Monster("Giant",8,1,p,{100.f,150.f}){
    createBodyPart({50.f,50.f},{25.f,0.f},sf::Color(248,194,145));
    createBodyPart({10.f,10.f},{35.f,10.f},sf::Color::Black);
    createBodyPart({10.f,10.f},{55.f,10.f},sf::Color::Black);
    createBodyPart({75.f,75.f},{12.5f,50.f},sf::Color(40,100,100));
    createBodyPart({12.5f,50.f},{0.f,50.f},sf::Color(248,194,145));
    createBodyPart({12.5f,50.f},{87.5f,50.f},sf::Color(248,194,145));
    createBodyPart({25.f,25.f},{20.f,125.f},sf::Color(248,194,145));
    createBodyPart({25.f,25.f},{55.f,125.f},sf::Color(248,194,145));
    attitude=Neutral;
    defaultAttitude=Neutral;
    fightUntilDeath=true;
    bodyType=LIVING;
}
void Giant::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
        float attackDamage=(std::rand() % (int)(damage*0.2+1))+damage-damage*0.1;
        Rock rock(getCenter(),mousePos,damage,false);
        projectiles.push_back(std::make_unique<Rock>(rock));
        attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}
