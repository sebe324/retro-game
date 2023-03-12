#include "Arrow.h"

Arrow::Arrow(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Arrow", dmg, sf::seconds(5),PHYSIC,p,{20.f,20.f},dest,100.f,attackMons){
createBodyPart({40.f,20.f},{0.f,0.f},sf::Color{70,50,0});
}
