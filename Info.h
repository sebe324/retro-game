#ifndef INFO_H
#define INFO_h

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <iostream>
#include <fstream>
class Info : public sf::Drawable{

public:
Button goBack;
Button next;
Button previous;
sf::Sprite background;
sf::Sprite image;
sf::Text description;
sf::Texture backgroundTexture;
sf::Texture imageTexture;
Info(sf::Font& font, std::string backgroundPath);
int counter=1;

void update(sf::Vector2f pos);
void checkClick(sf::Vector2f pos);
private:
    void updateTexture();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // INFO_H
