#include "World.h"

World::World(unsigned sizeX, unsigned sizeY, std::vector<float> biomeValues){
    
}

World::World(unsigned sizeX, unsigned sizeY, unsigned seed, unsigned octaves, float bias){
    tilesAmount = sizeX * sizeY * biomeTileSize*biomeTileSize;
    tilesToDraw=sf::VertexArray(sf::Quads,tilesAmount*4);
    rnd.seed=seed;
    this->octaves=octaves;
    this->bias=bias;
}

void World::generateNewWorld(unsigned seed){
    //Generate biomes
    generateBiomes();
    //Randomize tiles for more diversity

    //Biome blend

    //Generate rivers
}

void World::generateBiomes(){
    std::vector<float> noiseValues2d;
    std::vector<float> randomValues(sizeX*sizeY);
    for(unsigned i = 0; i < sizeX*sizeY; i++) randomValues=(float)rnd.rndInt(0,100);

    noiseValues2d = rnd.perlin2d(randomValues,sizeX,sizeY,octaves,bias);

    for(unsigned row = 0; row<sizeX; row++){
        for(unsigned col = 0; col<sizeY; col++){
            int index = row*sizeX+col;
            auto value=noiseValues2d[index];
            if (value<=30) biomes[index]=Biomes::DEADLANDS;
            else if (value>30&&value<60) biomes[index]=Biomes::PLAINS;
            else if (value>=60&&value<80) biomes[index]=Biomes::TOXIC_SWAMP;
            else if (value>=80&&value<100) biomes[index]=Biomes::DESERT;
            else if (value>=100) biomes[index]=Biomes::FIRE_REALM;
        }
    }
}
void World::update(sf::Time &elapsed, const sf::Vector2f &playerPos){
    //Change which biomes to show based on the player's position
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(tilesToDraw);
    //target.draw(biomesNearPlayer);
}