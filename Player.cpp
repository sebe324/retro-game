#include "Player.h"

Player::Player(std::string n, float d, float as, float spd, int l, sf::Vector2f p, sf::Vector2f s) : Character(n,d,as,spd,l,p, s){
    experience=0;
createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(250,177,160));
createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(99,110,114));
createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(116,118,255));
createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(116,118,255));
createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(45,52,54));
createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(45,52,54));
createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(55,62,64));
createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(55,62,64));
setExpRequired();
}
Player::Player() : Character(){}

bool Player::addExp(int n){
experience+=n;
if(experience>=expRequired){
experience-=expRequired;
levelUp();
setExpRequired();
return true;
}
return false;
}

int Player::getExp(){
return experience;
}

int Player::getExpRequired(){
return expRequired;
}
void Player::setExpRequired(){
    if(level>0 && level<10) expRequired=100;
    else if(level>=10 && level<20) expRequired=150;
    else if(level>=20 && level<30) expRequired=200;
    else if(level>=30) expRequired=300;
}

void Player::movementWSAD(bool b){
if(b){
    keyUp=sf::Keyboard::W;
    keyDown=sf::Keyboard::S;
    keyLeft=sf::Keyboard::A;
    keyRight=sf::Keyboard::D;
    keyRightAttack=sf::Keyboard::E;
    keyLeftAttack=sf::Keyboard::Q;
}
else{
keyUp=sf::Keyboard::Up;
    keyDown=sf::Keyboard::Down;
    keyLeft=sf::Keyboard::Left;
    keyRight=sf::Keyboard::Right;
    keyRightAttack=sf::Keyboard::E;
    keyLeftAttack=sf::Keyboard::Q;
}
}
