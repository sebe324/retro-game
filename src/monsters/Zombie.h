#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Monster.h"

class Zombie : public Monster{
    public:
        Zombie(sf::Vector2f p);
        Zombie();
        void wakeUp();
        void goSleep();
};
#endif // ZOMBIE_H
