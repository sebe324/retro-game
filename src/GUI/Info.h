#ifndef INFO_H
#define INFO_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * Info.h
 * 
 * Menu that gives you information on the different monsters on screen
 * Plan: Add button that gives information on controls
 */

class Info : public sf::Drawable {

    public:
        Button goBack;
        Button next;
        Button previous;
        Button controls;

        sf::Sprite background;
        sf::Sprite image;
        sf::Text description;
        sf::Texture backgroundTexture;
        sf::Texture imageTexture;

        Info (sf::Font& font, std::string backgroundPath);
        int counter = 1;

        void update(sf::Vector2f pos);
        void checkClick(sf::Vector2f pos);
    private:
        void updateTexture();
        void displayControls();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // INFO_H
