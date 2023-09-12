#include "Info.h"

Info::Info (sf::Font& font, std::string backgroundPath) {
    goBack = Button("Menu", 60, sf::Color::Black, {650,650}, {250.f,100.f}, sf::Color(92,64,51), font);
    goBack.hoverContentColor = sf::Color::White;
    next = Button(">", 70, sf::Color::Black, {800,800}, {100.f,100.f}, sf::Color(100,100,100), font);
    next.hoverContentColor = sf::Color::White;
    previous = Button("<", 70, sf::Color::Black, {650,800}, {100.f,100.f}, sf::Color(100,100,100), font);
    previous.hoverContentColor = sf::Color::White;
    controls = Button("Controls", 60, sf::Color::Black, {650, 500}, {250.f, 100.f}, sf::Color(92,64,51), font);
    controls.hoverContentColor = sf::Color::White;

    if (!backgroundTexture.loadFromFile(backgroundPath)) {}
    background.setTexture(backgroundTexture);

    description.setFont(font);
    description.setFillColor(sf::Color::White);
    description.setString("gg");
    updateTexture();
}

void Info::update (sf::Vector2f pos) {
    goBack.update(pos);
    next.update(pos);
    previous.update(pos);
    controls.update(pos);
}
void Info::checkClick (sf::Vector2f pos) {
    if (controls.click(pos)) {
        displayControls();
    }
    else if (next.click(pos)) {
        counter++; 
        updateTexture();
    }
    else if (previous.click(pos)) { 
        counter--; 
        updateTexture();
    }
}

void Info::draw (sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(background);
    target.draw(goBack);
    target.draw(next);
    target.draw(previous);
    target.draw(description);
    target.draw(controls);
    //target.draw(image);
}

void Info::updateTexture() {
    if (counter > 10) 
        counter = 10;
    else if (counter < 1) 
        counter = 1;
    else {
        if (!imageTexture.loadFromFile("../description/"+std::to_string(counter)+".png")) {}
        image.setTexture(imageTexture);
        std::string tmp;
        std::string elo;
        std::ifstream desc("../description/"+std::to_string(counter)+".txt");
        while (getline(desc,tmp)) {
            elo += tmp;
            elo += "\n";
        }
        description.setString(elo);
        desc.close();
    }
}

void Info::displayControls() {
    std::string tmp;
    std::string elo;
    std::ifstream controlScreen("../description/controls.txt");
    while (getline(controlScreen, tmp)) {
        elo += tmp;
        elo += "\n";
    }
    description.setString(elo);
    controlScreen.close();
}
