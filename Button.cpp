#include "Button.h"

Button::Button(){}

Button::Button(std::string text, int charSize, sf::Color contentColor, sf::Vector2f bPos, sf::Vector2f bSize, sf::Color bodyColor, sf::Font &font){
sf::RectangleShape b(bSize);
b.setFillColor(bodyColor);
b.setPosition(bPos);
body=b;
originalBodyColor=bodyColor;
originalContentColor=contentColor;

hoverBodyColor=bodyColor;
hoverContentColor=contentColor;

activeBodyColor=bodyColor;
activeContentColor=contentColor;
content.setString(text);
content.setFillColor(contentColor);
content.setFont(font);
content.setCharacterSize(charSize);

content.setPosition(body.getPosition().x+(body.getSize().x)/2-(content.getGlobalBounds().width/2),body.getPosition().y);
}

bool Button::contains(sf::Vector2f pos){
    if(body.getPosition().x<pos.x && body.getPosition().x+body.getSize().x>pos.x &&
       body.getPosition().y<pos.y && body.getPosition().y+body.getSize().y>pos.y
       ) return true;
    else return false;
}

bool Button::click(sf::Vector2f pos){
if(contains(pos)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;
else return false;
}
void Button::update(sf::Vector2f pos){
    if(click(pos)){
            body.setFillColor(activeBodyColor);
            content.setFillColor(activeContentColor);
    }
    else if(contains(pos)){
        body.setFillColor(hoverBodyColor);
        content.setFillColor(hoverContentColor);
    }
    else{
        body.setFillColor(originalBodyColor);
        content.setFillColor(originalContentColor);
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(body);
    target.draw(content);
}
