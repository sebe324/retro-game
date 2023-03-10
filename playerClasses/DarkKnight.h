#ifndef DARKKNIGHT_H
#define DARKKNIGHT_H

#include "Player.h"
class DarkKnight : public Player{

public:

DarkKnight(std::string n, sf::Vector2f p={0.f,0.f});

bool batForm=false;
float damageTemporary=0.f;
void ability1(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Vampiric circle
void ability2(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Fear The Power
void ability3(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Bat form
void update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>>& monsters);



};

#endif // DARKKNIGHT_H
