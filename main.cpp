#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Monster.h"
#include "Game.h"

int main(){

sf::RenderWindow window(sf::VideoMode(1000,1000),"Wojownicy");
Game game("texture.png", "font.ttf", &window);


sf::Clock clock;
sf::Time deltaTime;
sf::View view;
view.setCenter(game.player.getCenter());
window.setView(view);
window.setFramerateLimit(60);
while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
    }

    window.setView(view);
        game.update(deltaTime);
         view.setCenter(game.player.getCenter());
    window.clear();
    window.draw(game);
    window.display();
    deltaTime=clock.restart();
}
return 0;
}
