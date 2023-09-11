#include <SFML/Graphics.hpp>

#include "monsters/Monster.h"
#include "core/Game.h"
#include "enums/Modes.h"
#include "GUI/Menu.h"
#include "GUI/Button.h"
#include "GUI/worldCreator.h"
#include "GUI/Settings.h"
#include "GUI/Info.h"
#include "GUI/SubMenu.h"
#include <ctime>

/**
 * Main Program Loop
 */

int main() {

    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Retro-Game");
    sf::Image icon;
    if (icon.loadFromFile("../texture.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    Menu menu("../font.ttf","../texture.png");
    SubMenu gameOverMenu("../font.ttf", "../texture.png", "game_over");  // Menu to be presented upon the player's death
    SubMenu escKeyMenu("../font.ttf", "../texture.png", "escape_key");   // Menu to be presented upon pressing escape
    sf::Clock clock;
    sf::Time deltaTime;
    sf::View viewGame;
    sf::View viewUI;
    Game game("../texture.png", "../font.ttf", &window, &viewUI);
    int mode = MAIN_MENU;
    sf::Font font;
    if (!font.loadFromFile("../font.ttf")) {}
    Info info(font,"../texture.png");
    WorldCreator wCreator(font);
    Settings settings(font);
    window.setFramerateLimit(60);
    sf::Vector2u windowSize=window.getSize();
    float idk=(float)windowSize.y/windowSize.x;
    float idk2=(1.f-idk)*0.5;
    viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
    viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
    window.setView(viewUI);

    bool escapeKeyPressed = false; // This will allow the event loop to update the escape menu screen

    while (window.isOpen()) {
        window.clear();
        sf::Vector2i windowPosition=sf::Mouse::getPosition(window);
        sf::Vector2f mousePos=window.mapPixelToCoords(windowPosition);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed && mode != GAME_LOOP) {
                window.close(); // Only closes game if not currently playing game
            }
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize=window.getSize();
                float idk=(float)windowSize.y/windowSize.x;
                float idk2=(1.f-idk)*0.5;
                viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
                viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
                window.setView(viewUI);
            }
            switch(mode) {
                case MAIN_MENU:
                    menu.update(mousePos);
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (menu.bExitGame.click(mousePos)) {
                            window.close();
                            return 0;
                        }
                        if (menu.bNewGame.click(mousePos))      mode = WORLD_CREATOR;
                        if (menu.bDescription.click(mousePos))  mode = INFO_MENU;
                        if (menu.bSettings.click(mousePos))     mode = SETTINGS_MENU;
                    }
                    break;
                case WORLD_CREATOR:
                    wCreator.update(mousePos);
                    if (event.type == sf::Event::MouseButtonPressed) {
                        wCreator.checkClick(mousePos);
                        if (wCreator.bStartGame.click(mousePos)) {
                            game.changePlayerClass(wCreator.playerClass);
                            game.updateSettings(settings);
                            game.changeMap(wCreator.seed,wCreator.octaves, wCreator.bias);
                            mode = GAME_LOOP;
                            wCreator.clearVectors();
                        }
                        if (wCreator.bGoBack.click(mousePos)) {
                            mode = MAIN_MENU;
                        }
                    }
                    if (event.type == sf::Event::TextEntered) {
                        if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == 8) {
                            wCreator.seedInput.addCharacter(static_cast<char>(event.text.unicode));
                        }
                    }
                    break;
                case GAME_LOOP:
                    if (event.type == sf::Event::KeyPressed) {
                        // Sets the flag to present the ESC key menu if the player is not dead.
                        if (event.key.code == sf::Keyboard::Escape && !game.player->isDead()) {
                            escapeKeyPressed = !game.paused ? true : false;
                            game.paused = !game.paused;
                        }
                    }
                    if (event.type == sf::Event::Closed && !game.player->isDead()) {
                        escapeKeyPressed = !game.paused ? true : false;
                        game.paused = !game.paused;
                    }
                    break;
                case SETTINGS_MENU:
                    settings.update(mousePos);
                    settings.checkClick(mousePos);

                    if (settings.bGoBack.click(mousePos) && !escapeKeyPressed)
                        mode = MAIN_MENU; // If the escape key had not been pressed, we were in the main menu

                    if (settings.bGoBack.click(mousePos) && escapeKeyPressed) {
                        mode = GAME_LOOP; // If the escape key had been pressed, we were in the escape key menu
                        game.updateSettings(settings); // Updates the current game with the changes made in the settings
                    }
                    break;
                case INFO_MENU:
                    info.update(mousePos);
                    info.checkClick(mousePos);
                    if (info.goBack.click(mousePos)) {
                        mode = MAIN_MENU;
                    }
                    break;
                default: break;
            }
        }
        switch (mode) {
            case MAIN_MENU:
                window.draw(menu);
                break;
            case WORLD_CREATOR:
                window.draw(wCreator);
                break;
            case GAME_LOOP:
                window.setView(viewGame);
                mousePos = window.mapPixelToCoords(windowPosition);

                game.update(deltaTime, mousePos);
                viewGame.setCenter(game.player->getCenter());
                window.draw(game);

                //  Menu to be presented upon the player's death
                if (game.player->isDead()) {

                    game.paused = true;
                    mousePos = window.mapPixelToCoords(windowPosition);
                    gameOverMenu.update(mousePos);
                    window.draw(gameOverMenu);

                    if (event.type == sf::Event::MouseButtonPressed) {

                        if (gameOverMenu.bExitGame.click(mousePos)) {
                            window.close();
                            return 0;
                        }

                        if (gameOverMenu.bMainMenu.click(mousePos)) {
                            mode = MAIN_MENU;
                            game.paused = false;

                            // Recreating the game object was the only way I found to reset the game.
                            Game game("../texture.png", "../font.ttf", &window, &viewUI);
                        }
                    }
                }
                break;
            case SETTINGS_MENU:
                window.draw(settings);
                break;
            case INFO_MENU:
                window.draw(info);
                break;
            default: break;
        }

        // Menu to be presented upon pressing escape
        if (escapeKeyPressed && mode == GAME_LOOP) {

            game.paused = true;
            mousePos = window.mapPixelToCoords(windowPosition);
            escKeyMenu.update(mousePos);
            window.draw(escKeyMenu);

            if (event.type == sf::Event::MouseButtonPressed) {

                if (escKeyMenu.bResume.click(mousePos)) {
                    game.paused = false;
                    escapeKeyPressed = false;
                }
                if (escKeyMenu.bSettings.click(mousePos))
                    mode = SETTINGS_MENU;

                if (escKeyMenu.bExitGame.click(mousePos)) {
                    window.close();
                    return 0;
                }

                if (escKeyMenu.bMainMenu.click(mousePos)) {
                    mode = MAIN_MENU;
                    game.paused = false;
                    escapeKeyPressed = false;

                    // Recreating the game object was the only way I found to reset the game.

                    game.monsters.clear();
                    game.projectiles.clear();
                    for (auto &x : game.particleSystem)
                    {
                        x.emitters.clear();
                        x.textEmitters.clear();
                    }
                    Game game("../texture.png", "../font.ttf", &window, &viewUI);
                }
            }
        }

        window.display();
        deltaTime = clock.restart();
    }
    return 0;
}
