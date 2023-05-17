#include "ElementMage.h"
#include "../Monster.h"
#include "../Projectile/FireBall.h"

ElementMage::ElementMage(std::string n, sf::Vector2f p) :  Player(n,p,{50.f,90.f}){
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(250,177,160));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(183,21,64));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(116,118,255));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(116,118,255));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(7,153,146));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(150,150,100));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(240,185,59));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(12,36,97));
}

void ElementMage::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
       float attackDamage=(std::rand() % (int)(damage*0.2+1))+damage-damage*0.1;
FireBall fireBall(getCenter(),mousePos,damage,true);
projectiles.push_back(std::make_unique<FireBall>(fireBall));
attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}

void ElementMage::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){

}


void ElementMage::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){

}


void ElementMage::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){

}
