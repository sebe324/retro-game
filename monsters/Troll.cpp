#include "Troll.h"

Troll::Troll(sf::Vector2f p) : Monster("Troll",1,1,p,{60.f,90.f}){
    createBodyPart({30.f,30.f},{15.f,0.f},sf::Color(85,160,255));
    createBodyPart({6.f,6.f},{20,5.f},sf::Color::Black);
    createBodyPart({6.f,6.f},{31.f,5.f},sf::Color::Black);
    createBodyPart({40.f,30.f},{10.f,30.f},sf::Color(85,160,255));
    createBodyPart({40.f,15.f},{10.f,60.f},sf::Color(90,90,25));
    createBodyPart({10.f,15.f},{15.f,75.f},sf::Color(85,160,255));
    createBodyPart({10.f,15.f},{35.f,75.f},sf::Color(85,160,255));
    createBodyPart({10.f,22.f},{50.f,30.f},sf::Color(46,134,222));
    createBodyPart({10.f,22.f},{0.f,30.f},sf::Color(46,134,222));
}
void Troll::wakeUp(){

}
