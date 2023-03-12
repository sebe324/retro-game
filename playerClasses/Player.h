#ifndef PLAYER_H
#define PLAYER_H

#include "../particleSystem/particleSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "../Utilities/Utils.h"
#include "../Character.h"

class Monster;

class Player : public Character{
    public:
        sf::Keyboard::Key keyUp=sf::Keyboard::W;
        sf::Keyboard::Key keyDown=sf::Keyboard::S;
        sf::Keyboard::Key keyLeft=sf::Keyboard::A;
        sf::Keyboard::Key keyRight=sf::Keyboard::D;
        sf::Keyboard::Key keyRightAttack=sf::Keyboard::E;
        sf::Keyboard::Key keyLeftAttack=sf::Keyboard::Q;
        Player(std::string n, float d, float as, float spd, int l, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={10.f,10.f});
        Player(std::string n, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={10.f,10.f});
        Player();

        void addExp(int n);
        int getExp();
        int getExpRequired();
        bool checkLevelUp();
        void movementWSAD(bool b);
        virtual void update(sf::Time elapsed,std::vector<std::unique_ptr<Monster>>& monsters);
        virtual void ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem);
        virtual void ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem);
        virtual void ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem);

         sf::Time ability1Cooldown=sf::Time::Zero;
         sf::Time ability2Cooldown=sf::Time::Zero;
         sf::Time ability3Cooldown=sf::Time::Zero;
    private:
        int experience;
        int expRequired;

        void setExpRequired();
};

#endif // PLAYER_H
