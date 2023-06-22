#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
class Textbox : public sf::Drawable
{


public:

Textbox(std::string value, sf::Font& font, sf::Vector2f pos, unsigned int charSize=30, sf::Color color=sf::Color::Black, sf::Color bgColor=sf::Color::Transparent);
Textbox();
void isClicked(sf::Vector2f mousePos);
void addCharacter(char c);
sf::Text text;
sf::RectangleShape background;
std::string getTextValue();
void setMaxSize(int n);
private:
bool active=false;
int maxSize=1000;
sf::Vector2f minBackgroundSize;
void changeBackground();
void changeMinBackground();
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // TEXTBOX_H
