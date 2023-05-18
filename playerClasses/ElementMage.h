#ifndef ELEMENTMAGE_H
#define ELEMENTMAGE_H

#include "Player.h"

class Monster;

class ElementMage : public Player{

public:

ElementMage(std::string n, sf::Vector2f p={0.f,0.f});

void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);

void ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos); //Shield Bash
void ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos); //Holy Heal
void ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem,  std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos); //Bane of the dark




};
#endif // ELEMENTMAGE_H
