#include "Skeleton.h"

Skeleton::Skeleton(sf::Vector2f p) : Monster("Skeleton",2,8,p){

createBodyPart({28.f,28.f}, {11.f, 0.f}, sf::Color::White);
createBodyPart({10.f,30.f},{20.f,28.f},sf::Color::White);
createBodyPart({30.f,8.f},{10.f,38.f},sf::Color::White);
createBodyPart({8.f,15.f},{12.f,54.f},sf::Color::White);
createBodyPart({8.f,15.f},{30.f,54.f},sf::Color::White);
attitude=Aggressive;
defaultAttitude=Aggressive;
fightUntilDeath=true;
bodyType=UNDEAD;
}
