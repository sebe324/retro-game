#ifndef GAME_H
#define GAME_H

#include "Monster.h"
#include "Player.h"
#include "monsters/monsters.h"

#include "particleSystem/particleSystem.h"


#include <memory>
#include <iostream>
#include <sstream>
#include <SFML/Graphics/RenderWindow.hpp>
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
#include <iomanip>
#define FIXED_FLOAT(x) std::fixed <<std::setprecision(1)<<(x)
class Game : public sf::Drawable{

public:

std::vector<std::unique_ptr<Monster>> monsters;
std::vector<sf::Text> texts;
Player player;
ParticleSystem particles;
ParticleSystem particlesHp;
ParticleSystem particlesMana;
ParticleSystem particlesUI;
const sf::RenderWindow *window;
sf::Vector2i mousepos;
sf::Vector2f mouseglobal;
void update(sf::Time elapsed);
Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w);

private:

sf::Font font;
sf::Texture texture;
sf::Text playerLvl;
sf::Text playerHp;
sf::Text playerMana;
sf::VertexArray stats;
virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

void addText(std::string text, sf::Vector2f pos, sf::Color color);

void addMonster(int id,sf::Vector2f pos);
void statsSetup();

};

#endif // GAME_H

