#ifndef TROLL_H
#define TROLL_H

#include "Monster.h"

class Troll : public Monster{
    public:
        Troll(sf::Vector2f p);
        void wakeUp();
};

#endif // TROLL_H
