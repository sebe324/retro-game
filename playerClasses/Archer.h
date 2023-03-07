#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"

class Archer : public Player{

public:

Archer(std::string n, sf::Vector2f p={0.f,0.f});

void ability1(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Shield Bash
void ability2(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Holy Heal
void ability3(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Courage




};

#endif // ARCHER_H
