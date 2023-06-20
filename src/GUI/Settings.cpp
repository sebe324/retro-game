#include "Settings.h"

Settings::Settings(sf::Font& font){
bWSAD=Button("W-S-A-D",60,sf::Color::Green, {100.f,100.f},{250.f,100.f},sf::Color(92,64,51),font);
bWSAD.hoverContentColor=sf::Color::White;
bArrows=Button("Arrows",60,sf::Color::Red,{100.f,250.f},{250.f,100.f},sf::Color(92,64,51),font);
bArrows.hoverContentColor=sf::Color::White;
bSound=Button("Sound", 60, sf::Color(20,20,20),{100.f,400.f},{250.f,100.f},sf::Color(70,70,70),font);
bGoBack=Button("Menu", 60, sf::Color::Black,{700.f,100.f},{250.f,100.f},sf::Color(92,64,51),font);
bGoBack.hoverContentColor=sf::Color::White;

background=sf::RectangleShape({1000.f,1000.f});
background.setFillColor(sf::Color(100,100,100));
}

void Settings::checkClick(sf::Vector2f pos){
if(bWSAD.click(pos)){
    bWSAD.originalContentColor=sf::Color::Green;
    bArrows.originalContentColor=sf::Color::Red;
    WSAD=true;
}
if(bArrows.click(pos)){
    bArrows.originalContentColor=sf::Color::Green;
    bWSAD.originalContentColor=sf::Color::Red;
    WSAD=false;
}
}

void Settings::update(sf::Vector2f pos){
bWSAD.update(pos);
bArrows.update(pos);
bSound.update(pos);
bGoBack.update(pos);
}
void Settings::draw(sf::RenderTarget& target, sf::RenderStates states) const{
target.draw(background);
target.draw(bWSAD);
target.draw(bArrows);
target.draw(bSound);
target.draw(bGoBack);

}
