#ifndef SETTINGS_H
#define SETTINGS_H

#include "Button.h"

class Settings : public sf::Drawable {

    public:
        Button bWSAD;
        Button bArrows;

        Button bSound;
        Button bGoBack;
        bool WSAD=true;
        bool sound=true;
        sf::RectangleShape background;
        Settings(sf::Font& font);

        void update(sf::Vector2f pos);
        void checkClick(sf::Vector2f pos);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // SETTINGS_H
