#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

class Monster : public Character{
    public:
        float detectionRange;
        bool asleep=false;
        int direction=0;
        Monster(std::string name, int level, float dr, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={50.f,80.f});
        Monster();
        sf::Time moveDelay=sf::seconds(0);
        void randomMove(sf::Time elapsed);
        virtual void wakeUp();
        virtual void goSleep();
};

#endif // MONSTER_H
