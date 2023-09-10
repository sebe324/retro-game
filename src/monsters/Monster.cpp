#include "Monster.h"


Monster::Monster(std::string name, int level, float dr, sf::Vector2f p, sf::Vector2f s) : Character(name, 1,0.2,50,level,p,s) {
    detectionRange=dr;
}

Monster::Monster() : Character() {}

void Monster::randomMove(sf::Time elapsed) {
    if (!asleep) {
        moveDelay-=elapsed;
        if (moveDelay<=sf::Time::Zero) {
            direction=(std::rand()%5)-0;
            moveDelay=sf::seconds(3);
        }
        if (direction==0) moveUp(elapsed,0.2);
        else if (direction==1) moveDown(elapsed,0.2);
        else if (direction==2) moveLeft(elapsed,0.2);
        else if (direction==3) moveRight(elapsed,0.2);
    }
}

void Monster::pathFindTo(sf::Time elapsed, Character& character) {
    if (getDistanceX(character)<-80.f) moveRight(elapsed, 0.4);
    else if (getDistanceX(character)>80.f) moveLeft(elapsed, 0.4);
    if (getDistanceY(character)<-80.f) moveDown(elapsed, 0.4);
    else if (getDistanceY(character)>80.f) moveUp(elapsed, 0.4);
}
void Monster::runFrom(sf::Time elapsed, Character& character) {
    if (getDistanceX(character)<-0.f) moveLeft(elapsed, 1);
    else if (getDistanceX(character)>0.f) moveRight(elapsed, 1);
    if (getDistanceY(character)<0.f) moveUp(elapsed, 1);
    else if (getDistanceY(character)>0.f) moveDown(elapsed, 1);
}
void Monster::attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed) {
    if (attackDelay-elapsed<sf::Time::Zero) {
        SwordSwing swordSwing(getCenter(),mousePos,damage,false);
        projectiles.push_back(std::make_unique<SwordSwing>(swordSwing));
        attackDelay=sf::seconds(0.3)/attackSpeed;
    }
}
void Monster::makeDecision(sf::Time elapsed, Character& character, std::vector<std::unique_ptr<Projectile>> &projectiles) {

    float dist=getDistance(character);
    if (dist<350 && dist>100.f && attitude==Aggressive) { // if monster is agressive and character is in line of sight, move towards
        pathFindTo(elapsed,character);
        preyDetected=true;
    }
    else if (dist<=100.f && attitude==Aggressive) {
        attack(projectiles,character.getCenter(),elapsed);
        //attack if player is close

        if (!fightUntilDeath && getHealth()<0.3*getMaxHealth()) attitude=Cowardly; //run away if you can't win!
    }
    else if (dist<650.f && attitude==Aggressive && preyDetected) pathFindTo(elapsed, character);
    else if (dist>=650.f && attitude==Aggressive && preyDetected) preyDetected=false;
    else if (dist<300 && attitude==Cowardly) { //if character is too close, run away
        runFrom(elapsed,character);
        dangerDetected=true;
    }
    else if (dist>600 && attitude==Cowardly && dangerDetected) { // if monster gets far away, it will stop running
       dangerDetected=false;
    }
    else if (dangerDetected) {runFrom(elapsed,character); //run away
    }
    else randomMove(elapsed); //if nothing else, just move randomly

}
void Monster::wakeUp() {
    asleep=false;
}

void Monster::goSleep() {
    asleep=true;
}
