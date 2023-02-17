#include "Succubus.h"

Succubus::Succubus(sf::Vector2f p) : Monster("Succubus",1,1,p){
createBodyPart({20.f,10.f},{0.f,0.f},sf::Color(60,15,15));
createBodyPart({20.f,10.f},{31.f,0.f},sf::Color(60,15,15));
createBodyPart({28.f,28.f},{11.f,10.f},sf::Color(110,80,70));
createBodyPart({5.f,5.f},{16.f,15.f},sf::Color(52,152,219));
createBodyPart({5.f,5.f},{26.f,15.f},sf::Color(52,152,219));
createBodyPart({15.f,15.f},{17.5f,38.f},sf::Color(110,80,70));
createBodyPart({8.f,20.f},{14.f,48.f},sf::Color(110,80,70));
createBodyPart({8.f,20.f},{28.f,48.f},sf::Color(110,80,70));
attitude=Aggressive;
fightUntilDeath=false;
bodyType=INFERNAL;
}
