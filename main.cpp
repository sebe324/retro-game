#include <SFML/Graphics.hpp>

#include "Monster.h"
#include "Game.h"
#include "Menu.h"
#include "Button.h"
#include "worldCreator.h"
#include "Settings.h"
#include "Info.h"
#include <ctime>
int main(){
sf::RenderWindow window(sf::VideoMode(1600,1000),"Wojownicy");
Menu menu("font.ttf","texture.png");
sf::Clock clock;
sf::Time deltaTime;
sf::View viewGame;
sf::View viewUI;
Game game("texture.png", "font.ttf", &window, &viewUI);
int mode=1;
sf::Font font;
if(!font.loadFromFile("font.ttf")){}
Info info(font,"texture.png");
WorldCreator wCreator(font);
Settings settings(font);
window.setFramerateLimit(60);
sf::Vector2u windowSize=window.getSize();
   float idk=(float)windowSize.y/windowSize.x;
            float idk2=(1.f-idk)*0.5;
            viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
            viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
window.setView(viewUI);
while(window.isOpen()){
    window.clear();
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
        else if(event.type==sf::Event::Resized){
            sf::Vector2u windowSize=window.getSize();
            float idk=(float)windowSize.y/windowSize.x;
            float idk2=(1.f-idk)*0.5;
            viewUI.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
            viewGame.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
            window.setView(viewUI);
        }
        sf::Vector2i windowPosition=sf::Mouse::getPosition(window);
        sf::Vector2f mousePos=window.mapPixelToCoords(windowPosition);
        switch(mode){
        case 1:
                 menu.update(mousePos);
        if(event.type==sf::Event::MouseButtonPressed){
            if(menu.bExitGame.click(mousePos)){
                window.close();
                return 0;
            }
            if(menu.bNewGame.click(mousePos)) mode=2;
            if(menu.bDescription.click(mousePos)) mode=5;
            if(menu.bSettings.click(mousePos)) mode=4;
        }
        break;
        case 2:
              wCreator.update(mousePos);
            if(event.type==sf::Event::MouseButtonPressed){
                    wCreator.checkClick(mousePos);
                    if(wCreator.bStartGame.click(mousePos)){
                    game.changePlayerClass(wCreator.playerClass);
                    game.changeMap(wCreator.seed,wCreator.octaves, wCreator.bias);
                    mode=3;
                    wCreator.clearVectors();
                    }
                    if(wCreator.bGoBack.click(mousePos)){
                        mode=1;
                    }
            }
        break;
        case 3:
             if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Escape) game.paused=!game.paused;
           }
            if(event.type==sf::Event::TextEntered){

            game.combo+=(char)event.text.unicode;
            game.combo.erase(0,1);
        }
        break;
        case 4:
            settings.update(mousePos);
            settings.checkClick(mousePos);
            game.player->movementWSAD(settings.WSAD);
            if(settings.bGoBack.click(mousePos))mode=1;
        break;
        case 5:
            info.update(mousePos);
            info.checkClick(mousePos);
            if(info.goBack.click(mousePos)){
                mode=1;
            }
        break;
        }


    }
    switch(mode){
    case 1:
        window.draw(menu);
    break;
    case 2:
        window.draw(wCreator);
    break;
    case 3:
     window.setView(viewGame);
        game.update(deltaTime);
         viewGame.setCenter(game.player->getCenter());
   window.draw(game);
    break;
    case 4:
        window.draw(settings);
    break;
    case 5:
        window.draw(info);
    break;
    }

    window.display();
    deltaTime=clock.restart();
}
return 0;
}
