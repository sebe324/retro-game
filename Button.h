#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Button : public sf::Drawable{
public:

sf::RectangleShape body;
sf::Text content;
sf::Color originalBodyColor;
sf::Color originalContentColor;

sf::Color hoverBodyColor;
sf::Color hoverContentColor;

sf::Color activeBodyColor;
sf::Color activeContentColor;
bool contains(sf::Vector2i pos);
bool click(sf::Vector2i pos);
void update(sf::Vector2i pos);
Button();
Button(std::string text, int charSize, sf::Color contentColor, sf::Vector2f bPos, sf::Vector2f bSize, sf::Color bodyColor, sf::Font &font);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // BUTTON_H
