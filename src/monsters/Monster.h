#ifndef MONSTER_H
#define MONSTER_H

#include "../core/Character.h"
#include "../particleSystem/particleSystem.h"
#include "../enums/Attitude.h"
#include "../Projectile/Projectile.h"

class Monster : public Character{
    public:
        float detectionRange;
        bool asleep=false;
        bool dangerDetected=false;
        bool preyDetected=false;
        bool fightUntilDeath=false;
        int direction=0;
        Attitude attitude;
        Attitude defaultAttitude;
        Monster(std::string name, int level, float dr, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={50.f,80.f});
        Monster();
        sf::Time moveDelay=sf::seconds(0);
        void randomMove(sf::Time elapsed);
        void pathFindTo(sf::Time elapsed, Character& character);
        void runFrom(sf::Time elapsed, Character& character);
        void makeDecision(sf::Time elapsed, Character& character, std::vector<std::unique_ptr<Projectile>> &projectiles);
        void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);
        virtual void wakeUp();
        virtual void goSleep();

};

#endif // MONSTER_H
