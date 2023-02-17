#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Monster.h"
#include "Game.h"
#include "Menu.h"
#include "Button.h"
#include "worldCreator.h"
#include "Settings.h"
#include <ctime>
int main(){
sf::RenderWindow window(sf::VideoMode(1000,1000),"Wojownicy");
Game game("texture.png", "font.ttf", &window);
Menu menu("font.ttf","texture.png");
sf::Clock clock;
sf::Time deltaTime;
sf::View view;
int mode=1;
view.setCenter(game.player.getCenter());
//window.setView(view);
sf::Font font;
if(!font.loadFromFile("font.ttf")){}
WorldCreator wCreator(font);
Settings settings(font);
window.setFramerateLimit(60);
while(window.isOpen()){
    window.clear();
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
        sf::Vector2i windowPosition=sf::Mouse::getPosition(window);
        if(mode==1){
            menu.update(windowPosition);
        if(event.type==sf::Event::MouseButtonPressed){
            if(menu.bExitGame.click(windowPosition)){
                window.close();
                return 0;
            }
            if(menu.bNewGame.click(windowPosition)) mode=2;
            if(menu.bSettings.click(windowPosition)) mode=4;
        }
        }
        else if(mode==2){
            wCreator.update(windowPosition);
            if(event.type==sf::Event::MouseButtonPressed){
                    wCreator.checkClick(windowPosition);
                    if(wCreator.bStartGame.click(windowPosition)){
                    game.changeMap(wCreator.seed,wCreator.octaves, wCreator.bias);
                    mode=3;
                    wCreator.clearVectors();
                    }
                    if(wCreator.bGoBack.click(windowPosition)){
                        mode=1;
                    }
            }
        }
        else if(mode==4){
            settings.update(windowPosition);
            settings.checkClick(windowPosition);
            game.player.movementWSAD(settings.WSAD);
            if(settings.bGoBack.click(windowPosition))mode=1;
        }
        else if (mode==3){
           if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Escape) game.paused=!game.paused;
           }
            if(event.type==sf::Event::TextEntered){

            game.combo+=(char)event.text.unicode;
            game.combo.erase(0,1);
            std::cout<<game.combo<<"\n";
        }
        }
    }
    if(mode==3){
    window.setView(view);
        game.update(deltaTime);
         view.setCenter(game.player.getCenter());
   window.draw(game);
    }else if(mode==1) window.draw(menu);
    else if(mode==2) window.draw(wCreator);
    else if(mode==4) window.draw(settings);
    window.display();
    deltaTime=clock.restart();
}
return 0;
}
