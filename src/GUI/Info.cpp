#include "Info.h"

Info::Info (sf::Font& font, std::string backgroundPath) {
    
    // Enemies Button
    enemies = Button("Enemies", 60, sf::Color::Black, {650, 200}, {250.f,100.f}, sf::Color(92,64,51), font);
    enemies.hoverContentColor = sf::Color::White;

    // Classes button
    classes = Button("Classes", 60, sf::Color::Black, {650, 350}, {250.f,100.f}, sf::Color(92,64,51), font);
    classes.hoverContentColor = sf::Color::White;
    
    // Controls button
    controls = Button("Controls", 60, sf::Color::Black, {650,500}, {250.f,100.f}, sf::Color(92,64,51), font);
    controls.hoverContentColor = sf::Color::White;
    
    // Menu button
    goBack = Button("Menu", 60, sf::Color::Black, {650,650}, {250.f,100.f}, sf::Color(92,64,51), font);
    goBack.hoverContentColor = sf::Color::White;

    // < button
    previous = Button("<", 70, sf::Color::Black, {650,800}, {100.f,100.f}, sf::Color(100,100,100), font);
    previous.hoverContentColor = sf::Color::White;

    // > button
    next = Button(">", 70, sf::Color::Black, {800,800}, {100.f,100.f}, sf::Color(100,100,100), font);
    next.hoverContentColor = sf::Color::White;

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

    enemies.update(pos);
    classes.update(pos);
}

void Info::checkClick (sf::Vector2f pos) {
    if (controls.click(pos)) {
        menu = CONTROLS;
    } else if (enemies.click(pos)) {
        menu = ENEMIES;
    } else if (classes.click(pos)) {
        menu = CLASSES;
    } else if (next.click(pos)) {
        counter++;
    } else if (previous.click(pos)) {
        counter--;
    }
    updateTexture();
}

void Info::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(goBack);
    target.draw(next);
    target.draw(previous);
    target.draw(description);
    target.draw(controls);
    target.draw(enemies);
    target.draw(classes);
    target.draw(image);
}

void Info::updateTexture() {

    std::string text = "../src/description/";

    switch (menu) {
        case CONTROLS:
            text += "controls.txt";
            break;
        case CLASSES:
            if (counter > 4) {
                counter = 4;
            } else if (counter < 1) {
                counter = 1;
            }
            text += "classes/" + std::to_string(counter) + ".txt";
            break;
        case ENEMIES:
            if (counter > 10) {
                counter = 10;
            } else if (counter < 1) {
                counter = 1;
            }
            text += "enemies/" + std::to_string(counter) + ".txt";
            break;
        default: break;
    }

    // if (!imageTexture.loadFromFile("../src/description/1.png")) {}
    // image.setTexture(imageTexture);
    std::string tmp;
    std::string elo;
    std::ifstream desc(text);
    while (getline(desc,tmp)) {
        elo += tmp + "\n";
    }
    description.setString(elo);
    desc.close();
}

