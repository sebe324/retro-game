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
: nearbyBiomes(9, sf::VertexArray(sf::Quads, biomeTileSize*biomeTileSize*4))
{
    playerBiomePos=sf::Vector2i(-1,-1);
    this->sizeX=sizeX;
    this->sizeY=sizeY;
    tilesAmount = sizeX * sizeY * biomeTileSize*biomeTileSize;
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

    rnd.seed=seed;
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

void World::generateTiles(const sf::Vector2f &playerPos){
    
    //In the memory only 9 biomes will be loaded.
    //Rest will be stored in an algorithm.

    //I have no idea what I'm doing, but I hope this thing will work

    int idkX=(int)playerPos.x >> 12;
    int idkY=(int)playerPos.y >> 12;
    //iterate through all 9 nearby biomes and generate tiles
    for(unsigned y = 0; y < 3; y++)
    for(unsigned x = 0; x < 3; x++){
    rnd.seed=seed;
    int tmpX=Utils::clamp(idkX-1+x,0,sizeX-1);
    int tmpY=Utils::clamp(idkY-1+y,0,sizeY-1);
    auto& nearbyBiome = nearbyBiomes[y*3+x];
    for(unsigned tileY = 0; tileY < biomeTileSize; tileY++){
        for(unsigned tileX = 0; tileX < biomeTileSize; tileX++){

            unsigned tileIndex = tileY*biomeTileSize+tileX;
            
            //get current biome

            Biomes biomeID = getBiome(tmpX,tmpY);
            //randomize texture
            int textureID = rnd.rndInt(0,7);

            //Get biome coords in game

            sf::Vector2f biomeCoords(tmpX<<12, tmpY<<12);
            //set the tile's position
            sf::Vector2f tileCoords(tileX*tileSize,tileY*tileSize);


            nearbyBiome[tileIndex*4+0].position=biomeCoords+tileCoords+sf::Vector2f(0.f,0.f);
            nearbyBiome[tileIndex*4+1].position=biomeCoords+tileCoords+sf::Vector2f(tileSize,0.f);
            nearbyBiome[tileIndex*4+2].position=biomeCoords+tileCoords+sf::Vector2f(tileSize,tileSize);
            nearbyBiome[tileIndex*4+3].position=biomeCoords+tileCoords+sf::Vector2f(0.f,tileSize);
            

            //set the tile's texture
            sf::Vector2f textureCoords(16*textureID,16*biomeID);

            nearbyBiome[tileIndex*4+0].texCoords=textureCoords+sf::Vector2f(0.f,0.f);
            nearbyBiome[tileIndex*4+1].texCoords=textureCoords+sf::Vector2f(16.f,0.f);
            nearbyBiome[tileIndex*4+2].texCoords=textureCoords+sf::Vector2f(16.f,16.f);
            nearbyBiome[tileIndex*4+3].texCoords=textureCoords+sf::Vector2f(0.f,16.f);
            

            //nearbyBiome[tileY*biomeTileSize+tileX]
        }
    }
    }
    rnd.seed=seed;
}

void World::generateRivers(){
    //I'm not sure how to exactly implement it. I'll do it later.
}
void World::update(sf::Time &elapsed, const sf::Vector2f &playerPos){

    int tmpX=(int)playerPos.x >> 12;
    int tmpY=(int)playerPos.y >> 12;

    //if player has moved into a new biome
    if(playerBiomePos.x !=tmpX || playerBiomePos.y !=tmpY){
        //generate tiles for surrounding biomes
        playerBiomePos.x=tmpX;
        playerBiomePos.y=tmpY;
        //std::cout<<"tmpX "<<tmpX<<std::endl;
        //std::cout<<"tmpY "<<tmpY<<std::endl;
        generateTiles(playerPos);
    }
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

void World::setTexture(const std::string &path){
    if(!tileTexture.loadFromFile(path)){
        std::cout<<"TEXTURE FAILED TO LOAD!";
    }
}
void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.texture=&tileTexture;
    for(auto& b : nearbyBiomes ) target.draw(b,states);
}