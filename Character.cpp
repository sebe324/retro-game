#include "Character.h"
Character::Character(std::string n, float d, float as, float spd, int l, sf::Vector2f p, sf::Vector2f s){
name=n;
damage=d;
attackSpeed=as;
speed=spd;
hitbox= sf::Rect<float>(p.x,p.y,s.x,s.y);
setLevel(l);
bodyParts=sf::VertexArray(sf::Quads,0);
attackDelay=sf::Time::Zero;
}
Character::Character(){}

sf::Vector2f Character::getCenter() const{
return {hitbox.left+hitbox.width*0.5f, hitbox.top+hitbox.height*0.5f};
}


void Character::update(sf::Time elapsed){
regenerate(elapsed);
attackDelay-=elapsed;
move();
}
void Character::moveUp(sf::Time elapsed, float multiplier){
velocity.y-=speed*elapsed.asSeconds()*multiplier;
}
void Character::moveDown(sf::Time elapsed, float multiplier){
velocity.y+=speed*elapsed.asSeconds()*multiplier;
}
void Character::moveLeft(sf::Time elapsed, float multiplier){
float tmp=velocity.x;
velocity.x-=speed*elapsed.asSeconds()*multiplier;
if(tmp>=0 && velocity.x<0 && !left){
for(int i=0; i<bodyPartsNumber*4; i++){
    bodyParts[i].position.x=mirrorXf(bodyParts[i].position.x,hitbox.left,hitbox.left+hitbox.width);
}
left=true;
}
}
void Character::moveRight(sf::Time elapsed, float multiplier){
float tmp=velocity.x;
velocity.x+=speed*elapsed.asSeconds()*multiplier;
if(tmp<=0 && velocity.x>0 && left){
for(int i=0; i<bodyPartsNumber*4; i++){
     bodyParts[i].position.x=mirrorXf(bodyParts[i].position.x,hitbox.left,hitbox.left+hitbox.width);
}
left=false;
}
}
void Character::move(){
velocity.y*=0.9;
velocity.x*=0.9;
for(int i=0; i<bodyPartsNumber*4; i++){
bodyParts[i].position+=velocity;
}
hitbox.top+=velocity.y;
hitbox.left+=velocity.x;
}
bool Character::attack(Character &character, sf::Time elapsed){
    if(attackDelay-elapsed<sf::Time::Zero){
character.removeHealth(damage);
attackDelay=sf::seconds(1)/attackSpeed;
return true;
    }
    return false;
}

void Character::regenerate(sf::Time elapsed){
addHealth(healthRegen*elapsed.asSeconds());
addMana(manaRegen*elapsed.asSeconds());
}
bool Character::isDead(){
if(health<=0) return true;
else return false;
}

void Character::setLevel(int n){
while(level<n) levelUp();
}

void Character::levelUp(){
addMaxHealth(10);
addHealth(10);
addMaxMana(10);
addMana(10);
speed+=2;
damage+=1;
level++;
healthRegen+=0.2;
manaRegen+=0.2;
}
void Character::setHealth(float n){
if(n>maxHealth) health=maxHealth;
else if(n<=0) health=0;
else health=n;
}

void Character::addHealth(float n){
setHealth(health+n);
}
void Character::removeHealth(float n){
setHealth(health-n);
}
void Character::setMaxHealth(float n){
if(n<=0) maxHealth=1;
else maxHealth=n;
}

void Character::addMaxHealth(float n){
setMaxHealth(maxHealth+n);
}

void Character::setHealthRegen(float n){
healthRegen=n;
}

void Character::setMana(float n){
if(n>maxMana) mana=maxMana;
else if(n<=0) mana=0;
else mana=n;
}

void Character::addMana(float n){
setMana(mana+n);
}

void Character::setMaxMana(float n){
if(n<=0) maxMana=1;
else maxMana=n;
}
void Character::addMaxMana(float n){
setMaxMana(maxMana+n);
}
void Character::setManaRegen(float n){
manaRegen=n;
}

int Character::getLevel() const{
return level;
}
float Character::getHealth() const{
return health;
}
float Character::getMaxHealth() const{
return maxHealth;
}
float Character::getHealthRegen() const{
return healthRegen;
}
float Character::getMana() const{
return mana;
}
float Character::getMaxMana() const{
return maxMana;
}
float Character::getManaRegen() const{
return manaRegen;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
target.draw(bodyParts,states);
}

void Character::createBodyPart(sf::Vector2f s, sf::Vector2f offset, sf::Color color){
bodyPartsNumber++;
bodyParts.resize(bodyPartsNumber*4);
    bodyParts[(bodyPartsNumber*4)-1].position={hitbox.left+offset.x,hitbox.top+offset.y};
    bodyParts[(bodyPartsNumber*4)-1].color=color;
    bodyParts[(bodyPartsNumber*4)-2].position={hitbox.left+offset.x+s.x,hitbox.top+offset.y};
    bodyParts[(bodyPartsNumber*4)-2].color=color;
    bodyParts[(bodyPartsNumber*4)-3].position={hitbox.left+offset.x+s.x,hitbox.top+offset.y+s.y};
    bodyParts[(bodyPartsNumber*4)-3].color=color;
    bodyParts[(bodyPartsNumber*4)-4].position={hitbox.left+offset.x,hitbox.top+offset.y+s.y};
    bodyParts[(bodyPartsNumber*4)-4].color=color;
}
float Character::mirrorXf(float x, float borderL, float borderR){
float distance=x-borderL;
x=borderR-distance;
return x;
}

float Character::getDistance(Character& character) const{
return sqrt(pow(character.getCenter().x-getCenter().x,2)+pow(character.getCenter().y-getCenter().y,2));
}
float Character::getDistanceX(Character& character) const{
return getCenter().x-character.getCenter().x;
}

float Character::getDistanceY(Character& character) const{
return getCenter().y-character.getCenter().y;
}

