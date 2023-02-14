#include "ToxicLizard.h"

ToxicLizard::ToxicLizard(sf::Vector2f p) : Monster("Toxic Lizard",1,1,p,{92.f,50.f}){
createBodyPart({15.f,15.f},{13.f,25.f},sf::Color(60,60,60));
createBodyPart({32.f,20.f},{28.f,20.f},sf::Color(60,60,60));
createBodyPart({32.f,10.f},{60.f,30.f},sf::Color(60,60,60));
createBodyPart({5.f,5.f},{8.f,30.f},sf::Color(186,220,88));
createBodyPart({5.f,5.f},{18.f,30.f},sf::Color(186,220,88));
createBodyPart({10.f,10.f},{28.f,40.f},sf::Color(60,60,60));
createBodyPart({10.f,10.f},{43.f,40.f},sf::Color(60,60,60));
createBodyPart({10.f,10.f},{58.f,40.f},sf::Color(60,60,60));
attitude=Cowardly;
}
