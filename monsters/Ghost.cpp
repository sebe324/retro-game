#include "Ghost.h"

Ghost::Ghost(sf::Vector2f p) : Monster("Ghost",1,5,p){
createBodyPart({50.f,80.f},{0.f,0.f},sf::Color(126,214,223));
createBodyPart({5.f,5.f},{10.f,10.f},sf::Color(34,166,179));
createBodyPart({5.f,5.f},{35.f,10.f},sf::Color(34,166,179));
attitude=Neutral;
fightUntilDeath=true;
}
