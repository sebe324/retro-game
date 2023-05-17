#include "Archer.h"
#include "../Monster.h"

Archer::Archer(std::string n, sf::Vector2f p) :  Player(n,p,{50.f,90.f}){
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(250,177,160));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(120,120,40));
createBodyPart({5.f,15.f},{25.f,5.f},sf::Color(200,100,100));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(90,90,220));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(190,190,190));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(170,166,157));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(170,166,157));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(170,166,157));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(170,166,157));
}

void Archer::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
       float attackDamage=(std::rand() % (int)(damage*0.2+1))+damage-damage*0.1;
Arrow arrow(getCenter(),mousePos,damage,true);
projectiles.push_back(std::make_unique<Arrow>(arrow));
attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}


void Archer::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){
if(ability1Cooldown<=sf::Time::Zero){
    if(getMana()>=20.f){


        addMana(-20.f);
        ability1Cooldown=sf::seconds(5);
    }
}
}


void Archer::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){

}


void Archer::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){

}
