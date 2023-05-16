#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"
#include "../Projectile/Arrow.h"

class Monster;

class Archer : public Player{

public:

Archer(std::string n, sf::Vector2f p={0.f,0.f});

void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);

void ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem); //Triple shot
void ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem); //Trap
void ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem); //Idk




};

#endif // ARCHER_H
