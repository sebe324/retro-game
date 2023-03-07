#include "Vampire.h"

Vampire::Vampire(sf::Vector2f p) : Monster("Vampire",4,8,p){
   createBodyPart({28.f,28.f},{10.f,0.f},sf::Color(163,113,132));
    createBodyPart({5.f,5.f},{15.f,7.f},sf::Color(100,20,20));
    createBodyPart({5.f,5.f},{25.f,7.f},sf::Color(100,20,20));
    createBodyPart({28.f,40.f},{10.f,28.f},sf::Color::Black);
    createBodyPart({10.f,35.f},{0.f,28.f},sf::Color::White);
    createBodyPart({10.f,35.f},{38.f,28.f},sf::Color::White);
    createBodyPart({15.f,10.f},{5.f,68.f},sf::Color(60,60,60));
    createBodyPart({15.f,10.f},{27.f,68.f},sf::Color(60,60,60));
    attitude=Neutral;
    defaultAttitude=Neutral;
    fightUntilDeath=true;
    bodyType=UNDEAD;
}
