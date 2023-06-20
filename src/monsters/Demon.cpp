#include "Demon.h"

Demon::Demon(sf::Vector2f p) : Monster("Demon",1,5,p){
createBodyPart({28.f,28.f},{11.f,15.f},sf::Color(192,57,43));
createBodyPart({11.f,20.f},{0.f,0.f},sf::Color::White);
createBodyPart({11.f,15.f},{39.f,5.f},sf::Color::White);
createBodyPart({5.f,5.f},{16.f,20.f},sf::Color(70,20,20));
createBodyPart({5.f,5.f},{25.f,20.f},sf::Color(70,20,20));
createBodyPart({40.f,20.f},{5.f,43.f},sf::Color(192,57,43));
createBodyPart({10.f,10.f},{10.f,63.f},sf::Color(192,57,43));
createBodyPart({10.f,10.f},{30.f,63.f},sf::Color(192,57,43));
attitude=Aggressive;
defaultAttitude=Aggressive;
fightUntilDeath=true;
bodyType=INFERNAL;
damageMultiplier[FIRE]=0.5f;
}
