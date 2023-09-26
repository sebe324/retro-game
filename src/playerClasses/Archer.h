#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"
#include "../Projectile/Arrow.h"
#include <memory>

/**
 * Archer Class
*/

class Monster;

class Archer : public Player {
    public:
        Archer(std::string n, sf::Vector2f p={0.f,0.f});

        void ability1(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem,  
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos); //Triple shot

        void ability2(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem,  
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos); //Trap
                        
        void ability3(std::vector<std::unique_ptr<Monster>>& monsters, 
                        std::vector<ParticleSystem> &particleSystem,  
                        std::vector<std::unique_ptr<Projectile>> &projectiles, 
                        sf::Vector2f mousePos); //Dash
    
};

#endif // ARCHER_H
