#ifndef GAME_H
#define GAME_H

#include "Monster.h"
#include "Player.h"
#include "monsters/monsters.h"

#include "particleSystem/particleSystem.h"
#include "noise/perlinNoise.h"

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
bool paused=false;
bool isMapActive=true;
void update(sf::Time elapsed);

void changeMap(uint32_t seed, int octaves, float bias);
Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w);

private:

int playerXmap;
int playerYmap;

sf::Font font;
sf::Texture texture;
sf::Text playerLvl;
sf::Text playerHp;
sf::Text playerMana;
sf::Text playerExpProgress;
sf::VertexArray stats;
sf::VertexArray gameMap;
sf::VertexArray actualMap;
sf::VertexArray playerOnMap;
sf::RectangleShape mapBorder;
Rnd rnd;
std::vector<float> noiseValues2d;
virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

void addText(std::string text, sf::Vector2f pos, sf::Color color);

void addMonster(int id,sf::Vector2f pos);

void generateMonster();
void statsSetup();
void updateMap();
void updateParticles(sf::Time& elapsed);
void playerAttack(sf::FloatRect& attackRange, sf::Time& elapsed);
int getBiome(sf::Vector2f pos);
};

#endif // GAME_H

