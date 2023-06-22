#include "SwordSwing.h"

SwordSwing::SwordSwing(sf::Vector2f p, sf::Vector2f dest, float dmg, bool attackMons) : Projectile("Sword Swing", dmg, sf::seconds(.5),PHYSIC,p,{40.f,60.f},dest,250.f,attackMons){
createBodyPart({40.f,60.f},{0.f,0.f},sf::Color::White);

rotate(atan2(velY,velX)*180/3.14);
}

