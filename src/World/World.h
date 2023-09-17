#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../noise/perlinNoise.h"
#include "../core/Unit.h"
#include "Tile.h"
#include "../enums/Biomes.h"

class World : public sf::Drawable{

private:
    Rnd rnd;


    unsigned sizeX;
    unsigned sizeY;
    unsigned seed;
    unsigned tilesAmount;
    unsigned tileSize=50; // length of one tile in pixels
    unsigned biomeTileSize=50; // length of one biome in tiles

    unsigned octaves;
    float bias;
    
    sf::Texture tileTexture;
    //Tiles will be drawn in one draw function call to avoid lag.
    sf::VertexArray tilesToDraw; 
    sf::VertexArray spritesToDraw;
    std::vector<unsigned short> tilesInfo;
    std::vector<float> objsInfo;
    std::vector<Biomes> biomes;

    void generateBiomes();

    void generateRivers();

    void generateProps();

    void biomeBlend();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    World(unsigned sizeX, unsigned sizeY, std::vector<float> biomeValues);
    World(unsigned sizeX, unsigned sizeY, unsigned seed, unsigned octaves, float bias);
    
    void setTexture(const std::string& path);

    void generateNewWorld(unsigned seed);

    void update(sf::Time &elapsed, const sf::Vector2f &playerPos);
    unsigned getSizeX() const;
    unsigned getSizeY() const;

    unsigned getSeed() const;

    void setSizeX(unsigned x);

    void setSizeY(unsigned y); 
};
#endif