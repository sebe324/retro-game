#include "Menu.h"


Menu::Menu(std::string fontPath, std::string texturePath) {
    if (!font.loadFromFile(fontPath)) {}
    if (!texture.loadFromFile(texturePath)) {}
    bNewGame=Button("New Game", 62, sf::Color::Black, {250.f,200.f}, {500.f,150.f}, sf::Color(92,64,51), font);
    bNewGame.hoverContentColor=sf::Color::White;
    bNewGame.activeContentColor=sf::Color::White;
    b1v1=Button("Duel", 62, sf::Color(20,20,20), {250.f,400.f}, {500.f,150.f}, sf::Color(70,70,70), font);
    bDescription=Button("Info", 62, sf::Color::Black, {250.f, 600.f}, {240.f,150.f}, sf::Color(92,64,51), font);
    bDescription.hoverContentColor=sf::Color::White;
    bSettings=Button("Settings", 62, sf::Color::Black,{500.f, 600.f},{240.f,150.f},sf::Color(92,64,51), font);
    bSettings.hoverContentColor=sf::Color::White;
    bExitGame=Button("Exit", 62, sf::Color::Black, {250, 800.f}, {500.f,150.f}, sf::Color(92,64,51), font);
    bExitGame.hoverContentColor=sf::Color::White;
    bExitGame.activeContentColor=sf::Color::White;
    logo.setString("THE GAME");
    logo.setCharacterSize(80);
    logo.setFont(font);
    logo.setPosition(500-(logo.getGlobalBounds().width/2),50.f);
    logo.setFillColor(sf::Color::White);

    background.setTexture(texture);
}

void Menu::update(sf::Vector2f pos) {
    bNewGame.update(pos);
    b1v1.update(pos);
    bDescription.update(pos);
    bExitGame.update(pos);
    bSettings.update(pos);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(bNewGame);
    target.draw(b1v1);
    target.draw(bDescription);
    target.draw(bSettings);
    target.draw(bExitGame);
    target.draw(logo);
}
