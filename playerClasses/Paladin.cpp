#include "Paladin.h"
#include "../Monster.h"
Paladin::Paladin(std::string n, sf::Vector2f p) :  Player(n,p,{50.f,90.f}){
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(250,177,160));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(99,110,114));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(116,118,255));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(116,118,255));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(45,52,54));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(45,52,54));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(55,62,64));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(55,62,64));
}

void Paladin::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){
if(ability1Cooldown<=sf::Time::Zero){
    if(getMana()>=15.f){
        sf::FloatRect attackRange;
        if(left){attackRange=sf::FloatRect(hitbox.left-100.f-hitbox.width,hitbox.top-100.f,100.f+hitbox.width, 200.f);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter({hitbox.left,hitbox.top+25.f},10,{250,255},{250,255},{250,255});
        }
        else{attackRange=sf::FloatRect(hitbox.left,hitbox.top-100.f,100.f+hitbox.width, 200.f);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter({hitbox.left+hitbox.width,hitbox.top+25.f},10,{250,255},{250,255},{250,255});
        }
        for(int i=0; i<monsters.size(); i++){
            if(monsters[i]->hitbox.intersects(attackRange)){
                    monsters[i]->removeHealth(damage*0.5f+5);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(damage*0.5f+5,1),1,sf::Color::White,36);
                    if(left) monsters[i]->moveLeft(sf::seconds(1),1);
                    else monsters[i]->moveRight(sf::seconds(1),1);

            }
        }
    addMana(-15.f);
    ability1Cooldown=sf::seconds(2.5);
    }
}
}


void Paladin::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){
if(ability2Cooldown<=sf::Time::Zero){
    if(getMana()>=20.f){
            addHealth(getMaxHealth()*0.2);
            sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
            particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),15,{200,250},{200,250},{0,50});
            for(int i=0; i<monsters.size(); i++){
                if(monsters[i]->hitbox.intersects(attackRange) && (monsters[i]->bodyType==INFERNAL || monsters[i]->bodyType==UNDEAD)){
                    monsters[i]->removeHealth(damage*0.3f+3);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(damage*0.3f+3,1),1,sf::Color::White,36);
                }
            }
        addMana(-20.f);
        ability2Cooldown=sf::seconds(5);
    }

}
}


void Paladin::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, sf::Vector2f mousePos){
if(ability3Cooldown<=sf::Time::Zero){
    if(getMana()>=10.f){
        sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
        for(int i=0; i<monsters.size(); i++){
                sf::VertexArray lightning(sf::Quads,4);

                lightning[0].position=sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top)+sf::Vector2f(10.f,-100.f);
                lightning[1].position=sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top)+sf::Vector2f(40.f,-100.f);
                lightning[2].position=sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top)+sf::Vector2f(40.f,20.f);
                lightning[3].position=sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top)+sf::Vector2f(10.f,20.f);

                lightning[0].color=sf::Color::White;
                lightning[1].color=sf::Color::White;
                lightning[2].color=sf::Color::White;
                lightning[3].color=sf::Color::White;
                if(monsters[i]->hitbox.intersects(attackRange) && (monsters[i]->bodyType==INFERNAL || monsters[i]->bodyType==UNDEAD)){
                    monsters[i]->removeHealth(monsters[i]->getMaxHealth()*0.3f);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(monsters[i]->getMaxHealth()*0.3f,1),1,sf::Color::White,36);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(lightning,1);
                }
            }
    addMana(-10.f);
    ability3Cooldown=sf::seconds(1);
    }
}
}


