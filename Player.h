#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SFML/Window/Keyboard.hpp>
class Player : public Character{
    public:
        sf::Keyboard::Key keyUp=sf::Keyboard::W;
        sf::Keyboard::Key keyDown=sf::Keyboard::S;
        sf::Keyboard::Key keyLeft=sf::Keyboard::A;
        sf::Keyboard::Key keyRight=sf::Keyboard::D;
        sf::Keyboard::Key keyRightAttack=sf::Keyboard::E;
        sf::Keyboard::Key keyLeftAttack=sf::Keyboard::Q;
        Player(std::string n, float d, float as, float spd, int l, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={10.f,10.f});
        Player();

        bool addExp(int n);
        int getExp();
        int getExpRequired();
    private:
        int experience;
        int expRequired;

        void setExpRequired();

};

#endif // PLAYER_H
