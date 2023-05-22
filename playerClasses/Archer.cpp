#include "Archer.h"
#include "../Monster.h"
#include "../Projectile/Trap.h"

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

ability1Time=sf::seconds(5);
ability2Time=sf::seconds(10);
ability3Time=sf::seconds(2);

ability1Cost=20.f;
ability2Cost=50.f;
ability3Cost=15.f;
}

void Archer::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
       float attackDamage=(std::rand() % (int)(damage*0.2+1))+damage-damage*0.1;
Arrow arrow(getCenter(),mousePos,damage,true);
projectiles.push_back(std::make_unique<Arrow>(arrow));
attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}


void Archer::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
if(ability1Cooldown<=sf::Time::Zero){
    if(getMana()>=ability1Cost){

        Arrow arrow1(getCenter()+sf::Vector2f(0.f,10.f),mousePos,damage,true);
        Arrow arrow2(getCenter()-sf::Vector2f(0.f,10.f),mousePos,damage,true);
        Arrow arrow3(getCenter(),mousePos,damage,true);

        projectiles.push_back(std::make_unique<Arrow>(arrow1));
        projectiles.push_back(std::make_unique<Arrow>(arrow2));
        projectiles.push_back(std::make_unique<Arrow>(arrow3));

        removeMana(ability1Cost);
        ability1Cooldown=ability1Time;
    }
}
}


void Archer::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
    if(ability2Cooldown<=sf::Time::Zero){
        if(getMana()>=ability2Cost){
            Trap trap(mousePos,getCenter(),damage,true);

            projectiles.push_back(std::make_unique<Trap>(trap));
            removeMana(ability2Cost);
            ability2Cooldown=ability2Time;
        }
    }
}


void Archer::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos){
    if(ability3Cooldown<=sf::Time::Zero){
        if(getMana()>=ability3Cost){
            float tmpX=(mousePos.x-getCenter().x)/5;
            float tmpY=(mousePos.y-getCenter().y)/5;
            velocity+={tmpX,tmpY};

            particleSystem[PARTICLES_WORLD].addEmitter(getCenter(),5,{250,255},{250,255},{250,255});
            removeMana(ability3Cost);
            ability3Cooldown=ability3Time;
        }
    }
}
