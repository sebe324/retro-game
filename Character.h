#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ctime>


enum BodyType{
LIVING,
UNDEAD,
INFERNAL,
MACHINE
};
class Character : public sf::Drawable{
    public:
        float damage=0;
        float lastAttackDamage=0;
        float attackSpeed=0;
        float speed=0;
        bool left=true;
        BodyType bodyType=LIVING;
        std::string name;
        sf::Vector2f velocity;
        sf::Rect<float> hitbox;
        sf::VertexArray bodyParts;
        int bodyPartsNumber=0;
        sf::Time attackDelay;
        Character(std::string n, float d, float as, float spd, int l, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={50.f,80.f});
        Character();

        sf::Vector2f getCenter() const;

        void update(sf::Time elapsed);

        void moveUp(sf::Time elapsed, float multiplier=1);
        void moveDown(sf::Time elapsed, float multiplier=1);
        void moveLeft(sf::Time elapsed, float multiplier=1);
        void moveRight(sf::Time elapsed, float multiplier=1);
        void move();

        bool attack(Character &character, sf::Time elapsed);
        void regenerate(sf::Time elapsed);
        bool isDead();
        void setLevel(int n);
        void levelUp();

        void setHealth(float n);
        void addHealth(float n);
        void removeHealth(float n);
        void setMaxHealth(float n);
        void addMaxHealth(float n);
        void setHealthRegen(float n);

        void setMana(float n);
        void addMana(float n);
        void setMaxMana(float n);
        void addMaxMana(float n);
        void setManaRegen(float n);

        int getLevel() const;
        float getHealth() const;
        float getMaxHealth() const;
        float getHealthRegen() const;
        float getMana() const;
        float getMaxMana() const;
        float getManaRegen() const;

        float getDistance(Character& character) const;
        float getDistanceX(Character& character) const;
        float getDistanceY(Character& character) const;
    protected:

        void createBodyPart(sf::Vector2f p, sf::Vector2f offset, sf::Color color);
        int level=0;
        float mirrorXf(float x, float borderL, float borderR);
    private:

        float health=0;
        float maxHealth=0;
        float healthRegen=0;

        float mana=0;
        float maxMana=0;
        float manaRegen=0;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // CHARACTER_H
