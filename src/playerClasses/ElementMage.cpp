#include "ElementMage.h"
#include "../monsters/Monster.h"
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

ability1Time=sf::seconds(5.f);
ability2Time=sf::seconds(5.f);
ability3Time=sf::seconds(5.f);

ability1Cost=20.f;
ability2Cost=20.f;
ability3Cost=25.f;
}

void ElementMage::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
       float attackDamage=(std::rand() % (int)(damage*0.2+1))+damage-damage*0.1;
FireBall fireBall(getCenter(),mousePos,damage,true);
projectiles.push_back(std::make_unique<FireBall>(fireBall));
attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}

void ElementMage::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
    if(ability1Cooldown<=sf::Time::Zero){
         if(getMana()>=ability1Cost){
         FireBall fireBall1(getCenter(),getCenter()+sf::Vector2f(0.f,100.f),damage,true);
         FireBall fireBall2(getCenter(),getCenter()+sf::Vector2f(100.f,0.f),damage,true);
         FireBall fireBall3(getCenter(),getCenter()+sf::Vector2f(0.f,-100.f),damage,true);
         FireBall fireBall4(getCenter(),getCenter()+sf::Vector2f(-100.f,0.f),damage,true);

        projectiles.push_back(std::make_unique<FireBall>(fireBall1));
        projectiles.push_back(std::make_unique<FireBall>(fireBall2));
        projectiles.push_back(std::make_unique<FireBall>(fireBall3));
        projectiles.push_back(std::make_unique<FireBall>(fireBall4));
         removeMana(ability1Cost);
         ability1Cooldown=ability1Time;
         }
    }
}


void ElementMage::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
    if(ability2Cooldown<=sf::Time::Zero){
        if(getMana()>=ability2Cost){

            removeMana(ability2Cost);
            ability2Cooldown=ability2Time;
        }
    }
}


void ElementMage::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
 if(ability3Cooldown<=sf::Time::Zero){
        if(getMana()>=ability3Cost){
            addShield(10);
            particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter(),"ROCK SOLID",1,sf::Color(20,20,20),40);
            removeMana(ability3Cost);
            ability3Cooldown=ability3Time;
        }
    }
}
