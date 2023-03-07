#include "Archer.h"

Archer::Archer(std::string n, sf::Vector2f p) :  Player(n,p,{50.f,90.f}){
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(250,177,160));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(132,129,122));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(116,118,255));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(116,118,255));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(170,166,157));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(170,166,157));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(170,166,157));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(170,166,157));
}
void Archer::ability1(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles){

}


void Archer::ability2(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles){

}


void Archer::ability3(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles){

}
