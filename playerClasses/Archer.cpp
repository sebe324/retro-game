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
void Archer::ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){
addMana(-20.f);
}


void Archer::ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){

}


void Archer::ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem){

}
