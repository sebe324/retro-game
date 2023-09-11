#include "Player.h"
#include "../monsters/Monster.h"

Player::Player(std::string n, 
                float d, 
                float as, 
                float spd, 
                int l, 
                sf::Vector2f p, 
                sf::Vector2f s) 
                : Character(n,d,as,spd,l,p,s) {
    experience=0;
    setExpRequired();
    bodyType=LIVING;
}
Player::Player(std::string n, sf::Vector2f p, sf::Vector2f s) : Character(n,5,1,30,1,p,s) {
    experience=0;
    setExpRequired();
    bodyType=LIVING;
}
Player::Player() : Character() {}

void Player::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>>& monsters) {
    if (getHealth() > 0.0f) // This stops the player from regenerating after death
        regenerate(elapsed);

    attackDelay-=elapsed;
    ability1Cooldown-=elapsed;
    ability2Cooldown-=elapsed;
    ability3Cooldown-=elapsed;
    move();
}
void Player::addExp(int n) {
    experience+=n;
}
bool Player::checkLevelUp() {
    if (experience >= expRequired) {
        experience -= expRequired;
        levelUp();
        setExpRequired();
        return true;
    }
    return false;
}
int Player::getExp() {
    return experience;
}

int Player::getExpRequired() {
    return expRequired;
}
void Player::setExpRequired() {
    if (level>0 && level<10) expRequired=100;
    else if (level>=10 && level<20) expRequired=150;
    else if (level>=20 && level<30) expRequired=200;
    else if (level>=30) expRequired=300;
}

void Player::movementWSAD(bool b) {
    if (b) {
        keyUp=sf::Keyboard::W;
        keyDown=sf::Keyboard::S;
        keyLeft=sf::Keyboard::A;
        keyRight=sf::Keyboard::D;
    }
    else {
        keyUp=sf::Keyboard::Up;
        keyDown=sf::Keyboard::Down;
        keyLeft=sf::Keyboard::Left;
        keyRight=sf::Keyboard::Right;
    }
}

void Player::ability1(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem, 
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos) {}

void Player::ability2(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem, 
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos) {}

void Player::ability3(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem, 
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos) {}
