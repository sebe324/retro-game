#ifndef MENU_H
#define MENU_H

#include "../core/Game.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "../noise/perlinNoise.h"

class Menu : public sf::Drawable {
    public:

        sf::Text logo;
        Button bNewGame;
        Button b1v1;
        Button bDescription;
        Button bExitGame;
        Button bSettings;
        sf::Sprite background;

        Menu(std::string fontPath, std::string texturePath);
        void update(sf::Vector2f pos);

    private:

        sf::Font font;
        sf::Texture texture;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // MENU_H
