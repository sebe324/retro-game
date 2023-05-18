#include "Arrow.h"

Arrow::Arrow(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Arrow", dmg, sf::seconds(5),PHYSIC,p,{20.f,20.f},dest,300.f,attackMons){

createBodyPart({10.f,10.f},{50.f,0.f},sf::Color(150,150,150));
createBodyPart({50.f,10.f},{0.f,0.f},sf::Color(50,50,50));

rotate(atan2(velY,velX)*180/3.14);

disappearOnImpact=true;
}
