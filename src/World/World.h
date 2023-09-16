#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../noise/perlinNoise.h"
#include "../core/Unit.h"

class World : public sf::Drawable{

private:
    unsigned sizeX;
    unsigned sizeY;
    unsigned seed;
    sf::Texture tileTextures;
    //Tiles will be drawn in one draw function call to avoid lag.
    sf::VertexArray tiles_to_draw; 
    sf::VertexArray sprites_to_draw;
    std::vector<unsigned short> tiles_info;
    std::vector<float> objs_info;
    
    void generateBiomes();

    void generateRivers();

    void generateProps();

    void biomeBlend();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    World(unsigned sizeX, unsigned sizeY, std::vector<float> biomeValues);
    World(unsigned sizeX, unsigned sizeY, unsigned seed);

    void generateNewWorld(unsigned seed);

    unsigned getSizeX() const;
    unsigned getSizeY() const;

    unsigned getSeed() const;

    void setSizeX(unsigned x);

    void setSizeY(unsigned y); 
};
#endif