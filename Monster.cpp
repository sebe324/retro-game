#include "Monster.h"
#include <ctime>

Monster::Monster(std::string name, int level, float dr, sf::Vector2f p, sf::Vector2f s) : Character(name, 1,1,50,level,p,s){
detectionRange=dr;
}
Monster::Monster() : Character(){}
void Monster::randomMove(sf::Time elapsed){
if(!asleep){
moveDelay-=elapsed;
if(moveDelay<=sf::Time::Zero){
direction=(std::rand()%5)-0;
moveDelay=sf::seconds(3);
}
if(direction==0) moveUp(elapsed,0.2);
else if(direction==1) moveDown(elapsed,0.2);
else if(direction==2) moveLeft(elapsed,0.2);
else if(direction==3) moveRight(elapsed,0.2);
}
}

void Monster::wakeUp(){
asleep=false;
}

void Monster::goSleep(){
asleep=true;
}
