#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include "../Utilities/Utils.h"
#include <cmath>
#include <memory>
#include <iostream>
class Unit : public sf::Drawable {
    public:
        float speed=0;
        bool left=true;
        std::string name;
        sf::Vector2f velocity;
        sf::Rect<float> hitbox;
        sf::VertexArray bodyParts;
        int bodyPartsNumber=0;

        Unit(std::string n, sf::Vector2f p, sf::Vector2f s, float spd);
        Unit();

        sf::Vector2f getCenter() const;
        void update(sf::Time elapsed);

        void moveUp(sf::Time elapsed, float multiplier=1);
        void moveDown(sf::Time elapsed, float multiplier=1);
        void moveLeft(sf::Time elapsed, float multiplier=1);
        void moveRight(sf::Time elapsed, float multiplier=1);
        void move();

        float getDistance(Unit& unit) const;
        float getDistanceX(Unit& unit) const;
        float getDistanceY(Unit& unit) const;

        void rotate(float angle);
    protected:
        void createBodyPart(sf::Vector2f p, sf::Vector2f offset, sf::Color color);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // UNIT_H
