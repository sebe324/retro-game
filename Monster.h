#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include "particleSystem/particleSystem.h"


enum Attitude{
Aggressive=1,
Neutral=2,
Cowardly=3,
Fearful=4,
Curious=5
};

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
        bool makeDecision(sf::Time elapsed, Character& character);
        virtual void wakeUp();
        virtual void goSleep();

};

#endif // MONSTER_H
