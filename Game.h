#ifndef GAME_H
#define GAME_H

#include "Monster.h"
#include "playerClasses/Player.h"
#include "playerClasses/Paladin.h"
#include "playerClasses/DarkKnight.h"
#include "playerClasses/Archer.h"
#include "playerClasses/ElementMage.h"
#include "monsters/monsters.h"

#include "particleSystem/particleSystem.h"
#include "noise/perlinNoise.h"

#include <memory>
#include <iostream>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <iomanip>

#include "Utilities/Utils.h"
class Game : public sf::Drawable{

public:

std::vector<std::unique_ptr<Monster>> monsters;
std::vector<sf::Text> texts;
std::unique_ptr<Player> player;
ParticleSystem particles;
ParticleSystem particlesHp;
ParticleSystem particlesMana;
ParticleSystem particlesUI;
const sf::RenderWindow *window;
sf::View *viewUI;
sf::Vector2i mousepos;
sf::Vector2f mouseglobal;
std::string combo="00000000";
bool paused=false;
bool isMapActive=true;
void update(sf::Time elapsed);
void changeMap(uint32_t seed, int octaves, float bias);
Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w, sf::View* v);
void changePlayerClass(int playerClass);

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

