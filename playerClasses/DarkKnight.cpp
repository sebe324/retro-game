#include "DarkKnight.h"
#include "../Monster.h"

DarkKnight::DarkKnight(std::string n, sf::Vector2f p) :  Player(n,p,{50.f,90.f}){
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(230,200,200));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(48,59,107));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(111,30,81));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(111,30,81));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(19,15,64));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(19,15,64));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(19,15,64));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(19,15,64));
}
void DarkKnight::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){

    if(ability1Cooldown<=sf::Time::Zero){
        if(getMana()>=20.f){
            particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),15,{150,200},{0,50},{50,100});
            sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
            float healed=0;
            for(int i=0; i<monsters.size(); i++){
                if(monsters[i]->hitbox.intersects(attackRange)){
                    monsters[i]->removeHealth(damage*0.5f+10);
                    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(damage*0.5f+10,1),1,sf::Color::White,36);
                    addHealth(damage*0.25f+5);
                    healed+=(damage*0.25f+5);
                }
            }
        if(healed>0) particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(0.f,100.f),"+"+Utils::toString(healed,1)+"hp",1,sf::Color::Green,60);
        addMana(-20.f);
        ability1Cooldown=sf::seconds(5);

        }
    }
}



void DarkKnight::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){
    if(ability2Cooldown<=sf::Time::Zero){
        if(getMana()>=40.f){
            sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
            particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(), 15,{30,50},{30,50},{30,50});
            particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"FEAR THE DARK",1,sf::Color::Black,72);
            for(int i=0; i<monsters.size(); i++){
                if(monsters[i]->hitbox.intersects(attackRange)){
                        if(monsters[i]->getLevel()<level-5){
                            if(monsters[i]->bodyType==UNDEAD || monsters[i]->bodyType==INFERNAL){
                                    monsters[i]->attitude=Neutral;
                            }
                            else if(monsters[i]->bodyType==LIVING){
                                monsters[i]->removeHealth(damage*0.3f+5);
                                monsters[i]->attitude=Cowardly;
                                particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),Utils::toString(damage*0.3f+5,1),1,sf::Color::White,36);
                            }
                        }
                }
            }
        addMana(-40.f);
        ability2Cooldown=sf::seconds(10);
        }
    }
}


void DarkKnight::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){

    if(ability3Cooldown<=sf::Time::Zero){
        if(batForm){
            left=true;
            moveLeft(sf::seconds(1),0.1f);
            bodyParts.clear();
            createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(230,200,200));
            createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(48,59,107));
            createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(111,30,81));
            createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(111,30,81));
            createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(19,15,64));
            createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(19,15,64));
            createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(19,15,64));
            createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(19,15,64));
            batForm=false;
            ability3Cooldown=sf::seconds(20);
            for(int i=0; i<monsters.size(); i++){
                monsters[i]->attitude=monsters[i]->defaultAttitude;
            }
            damage=damageTemporary;
             particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"POOF",1,sf::Color(90,90,90),72);
            particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),20,{20,50},{20,50},{20,50});
        }
        else{
            if(getMana()>30.f){
                bodyParts.clear();
                moveRight(sf::seconds(1),0.1f);
                createBodyPart({30.f,10.f},{0.f,0.f},sf::Color::Black);
                createBodyPart({45.f,15.f},{15.f,10.f},sf::Color::Black);
                createBodyPart({30.f,10.f},{45.f,0.f},sf::Color::Black);
                createBodyPart({10.f,10.f},{25.f,25.f},sf::Color::Black);
                createBodyPart({10.f,10.f},{40.f,25.f},sf::Color::Black);
                createBodyPart({5.f,5.f},{35.f,15.f},sf::Color(111,30,81));
                createBodyPart({5.f,5.f},{45.f,15.f},sf::Color(111,30,81));
                ability3Cooldown=sf::seconds(1);
                addMana(-30.f);
                batForm=true;
                for(int i=0; i<monsters.size(); i++){
                    monsters[i]->attitude=Neutral;
                }
                damageTemporary=damage;
                damage=0.f;

                particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"POOF",1,sf::Color(90,90,90),72);
            particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),20,{20,50},{20,50},{20,50});
            }
        }
    }
}

void DarkKnight::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>>& monsters){
regenerate(elapsed);
attackDelay-=elapsed;
ability1Cooldown-=elapsed;
ability2Cooldown-=elapsed;
ability3Cooldown-=elapsed;
if(batForm)
for(int i=0; i<monsters.size(); i++)
    monsters[i]->attitude=Neutral;


move();
}
