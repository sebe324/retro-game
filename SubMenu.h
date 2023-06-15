#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "Game.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "noise/perlinNoise.h"

// This class was created to produce the game over and the ESC key screens. Since in both cases we have the creation of a menu, I use
// a single class for both of them. The class is an altered copy of the Menu class, but in an attempt do decrease the amount of
// changes to the original code, and due to my lack of familiarity with it, I chose to simply create a new class.
// The way I separated the ESC key menu from the game over one is not object oriented, so that is one way to improve this code.

class SubMenu : public sf::Drawable {

    public:
        sf::Text logo;
        Button bMainMenu;
        Button bResume;
        Button bExitGame;
        Button bSettings;

        sf::RectangleShape overlay;
        SubMenu(std::string fontPath, std::string texturePath, std::string menu_type);
        void update(sf::Vector2f pos);

    private:
        std::string menuType;
        sf::Font font;
        sf::Texture texture;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // SUB_MENU_H
