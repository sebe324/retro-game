#include "Giant.h"

Giant::Giant(sf::Vector2f p) : Monster("Giant",8,1,p,{100.f,150.f}){
createBodyPart({50.f,50.f},{25.f,0.f},sf::Color(248,194,145));
createBodyPart({10.f,10.f},{35.f,10.f},sf::Color::Black);
createBodyPart({10.f,10.f},{55.f,10.f},sf::Color::Black);
createBodyPart({75.f,75.f},{12.5f,50.f},sf::Color(40,100,100));
createBodyPart({12.5f,50.f},{0.f,50.f},sf::Color(248,194,145));
createBodyPart({12.5f,50.f},{87.5f,50.f},sf::Color(248,194,145));
createBodyPart({25.f,25.f},{20.f,125.f},sf::Color(248,194,145));
createBodyPart({25.f,25.f},{55.f,125.f},sf::Color(248,194,145));
attitude=Neutral;
fightUntilDeath=true;
}
