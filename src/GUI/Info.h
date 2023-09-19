#ifndef INFO_H
#define INFO_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "Button.h"
#include "../enums/InfoMenus.h"

/**
 * Info.h
 * 
 * Menu that gives you information on the different monsters on screen
 * Plan: Add button that gives information on controls
 */

class Info : public sf::Drawable {

    public:
        Button classes;
        Button enemies;
        Button controls;
        Button goBack;
        Button previous;
        Button next;
        
        sf::Sprite background;
        sf::Sprite image;
        sf::Text description;
        sf::Texture backgroundTexture;
        sf::Texture imageTexture;

        Info (sf::Font& font, std::string backgroundPath);
        int counter = 1;
        int menu = CONTROLS;

        void update(sf::Vector2f pos);
        void checkClick(sf::Vector2f pos);
    private:
        void updateTexture();
        void displayControls();
        void displayEnemies();
        void displayClasses();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // INFO_H
