#ifndef ELEMENTMAGE_H
#define ELEMENTMAGE_H

#include "Player.h"

class ElementMage : public Player{

public:

ElementMage(std::string n, sf::Vector2f p={0.f,0.f});

void ability1(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Shield Bash
void ability2(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Holy Heal
void ability3(std::vector<std::unique_ptr<Monster>>& monsters, ParticleSystem& particles); //Bane of the dark




};
#endif // ELEMENTMAGE_H
