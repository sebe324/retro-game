#include "World.h"

std::vector<sf::Color> World::biomeColors = {
sf::Color(64,64,122),
sf::Color(46, 113, 53),
sf::Color(116,146,76),
sf::Color(204,174,98),
sf::Color(100,20,20)
};
World::World(){}

World::World(unsigned sizeX, unsigned sizeY, std::vector<float> biomeValues){
    
}

World::World(unsigned sizeX, unsigned sizeY, unsigned seed, unsigned octaves, float bias)
{
    this->sizeX=sizeX;
    this->sizeY=sizeY;
    tilesAmount = sizeX * sizeY * biomeTileSize*biomeTileSize;
    tilesToDraw=sf::VertexArray(sf::Quads,tilesAmount*4);
    rnd.seed=seed;
    this->octaves=octaves;
    this->bias=bias;
    biomes.resize(sizeX*sizeY);
    generateBiomes();
}

void World::generateNewWorld(){
    //Generate biomes
    generateBiomes();
    //Randomize tiles for more diversity

    //Biome blend

    //Generate rivers
}

void World::generateBiomes(){
    std::vector<float> noiseValues2d;
    std::vector<float> randomValues(sizeX*sizeY);
    std::cout<<sizeX<<std::endl;
    for(unsigned i = 0; i < sizeX*sizeY; i++) randomValues[i]=(float)rnd.rndInt(0,100);

    noiseValues2d = rnd.perlin2d(randomValues,sizeX,sizeY,octaves,bias);
    std::cout<<"petla start";
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

Biomes World::getBiome(unsigned x, unsigned y) const{
    return biomes[y*sizeX+x];
}
void World::setSeed(unsigned s){
    seed = s;
    rnd.seed = s;
    generateNewWorld();
}
void World::setBias(float b){
    bias=b;
    generateNewWorld();
}

void World::setOctaves(unsigned o){
    octaves = o;
    generateNewWorld();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(tilesToDraw);
    //target.draw(biomesNearPlayer);
}