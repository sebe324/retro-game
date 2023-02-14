#include  "Game.h"
float randomize(int min, int n){
return (std::rand()%n)+min;
}

int clamp(int n, int min, int max){
if(n<min) return min;
else if(n>max) return max;
else return n;
}
Game::Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w){
if(!font.loadFromFile(fontPath)){}
if(!texture.loadFromFile(texturePath)){}
window=w;
player = Player("Player",1,2,100,5,{75000.f,75000.f},{50.f,90.f});
playerOnMap=sf::VertexArray(sf::Quads,4);
particles = ParticleSystem(sf::seconds(1.75));
particlesHp = ParticleSystem(sf::seconds(1));
particlesMana = ParticleSystem(sf::seconds(1));
particlesUI=ParticleSystem(sf::seconds(1.75));
statsSetup();
playerXmap=player.hitbox.left/3000.f;
playerYmap=player.hitbox.top/3000.f;

mapBorder=sf::RectangleShape({200.f,200.f});
mapBorder.setFillColor(sf::Color(0,0,0,0));
mapBorder.setOutlineThickness(5.f);
mapBorder.setPosition(5.f,5.f);
mapBorder.setOutlineColor(sf::Color::Black);
}

void Game::changeMap(uint32_t seed, int octaves, float bias){
    std::vector<float> randomValues2d(2500);
rnd.seed=seed;
for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
    randomValues2d[y*50+x]=rnd.rndInt(0,100);
}

noiseValues2d=rnd.perlin2d(randomValues2d,50,50,octaves,bias);
gameMap=sf::VertexArray(sf::Points, 50*50);
for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
    sf::Color color;
    auto value=noiseValues2d[y*50+x];
    if(value<=30) color=sf::Color(64,64,122);
    else if(value>30&&value<60) color=sf::Color(46, 113, 53);
    else if(value>60&&value<80) color=sf::Color(116,146,76);
    else if(value>80&&value<100) color=sf::Color(204,174,98);
    else if(value>=100) color=sf::Color(100,20,20);
    gameMap[y*50+x].color=color;
    gameMap[y*50+x].position={x,y};
}
actualMap=sf::VertexArray(sf::Quads,10000);
for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
auto& biome=gameMap[clamp(y,0,49)*50+clamp(x,0,49)];
    actualMap[(y*50+x)*4].color=biome.color;
    actualMap[(y*50+x)*4+1].color=biome.color;
    actualMap[(y*50+x)*4+2].color=biome.color;
    actualMap[(y*50+x)*4+3].color=biome.color;

    actualMap[(y*50+x)*4].position=biome.position*4.f+sf::Vector2f(5.f,5.f);
    actualMap[(y*50+x)*4+1].position=biome.position*4.f+sf::Vector2f(9.f,5.f);
    actualMap[(y*50+x)*4+2].position=biome.position*4.f+sf::Vector2f(9.f,9.f);
    actualMap[(y*50+x)*4+3].position=biome.position*4.f+sf::Vector2f(5.f,9.f);
}
updateMap();
}

void Game::updateMap(){
    playerXmap=player.hitbox.left/3000.f;
    playerYmap=player.hitbox.top/3000.f;
    auto& biome=gameMap[clamp(playerYmap,0,49)*50+clamp(playerXmap,0,49)];
    playerOnMap[0].color=sf::Color::Magenta;
    playerOnMap[1].color=sf::Color::Magenta;
    playerOnMap[2].color=sf::Color::Magenta;
    playerOnMap[3].color=sf::Color::Magenta;

    playerOnMap[0].position=biome.position*4.f+sf::Vector2f(5.f,5.f);
    playerOnMap[1].position=biome.position*4.f+sf::Vector2f(9.f,5.f);
    playerOnMap[2].position=biome.position*4.f+sf::Vector2f(9.f,9.f);
    playerOnMap[3].position=biome.position*4.f+sf::Vector2f(5.f,9.f);
}

void Game::update(sf::Time elapsed){
if(sf::Keyboard::isKeyPressed(player.keyUp)){ player.moveUp(elapsed); updateMap();}
if(sf::Keyboard::isKeyPressed(player.keyDown)){player.moveDown(elapsed); updateMap();}
if(sf::Keyboard::isKeyPressed(player.keyLeft)){ player.moveLeft(elapsed); updateMap();}
if(sf::Keyboard::isKeyPressed(player.keyRight)){player.moveRight(elapsed); updateMap();}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) isMapActive=true;
if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) isMapActive=false;
if(sf::Keyboard::isKeyPressed(player.keyRightAttack)){
    sf::FloatRect attackRange(player.hitbox.left-50.f,player.hitbox.top-50.f,150.f, 150.f);
   for(int i=0; i<monsters.size(); i++){
    if(attackRange.intersects(monsters[i]->hitbox)){
        monsters[i]->wakeUp();
        if(player.attack(*monsters[i],elapsed)){
                if(monsters[i]->attitude==Neutral )monsters[i]->attitude=Aggressive;
                particles.addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),SSTR(player.damage),1,font,sf::Color::White,36);
                if(monsters[i]->getHealth()<=0){
            particles.addEmitter(monsters[i]->bodyParts,monsters[i]->bodyPartsNumber);
            particles.addTextEmitter(monsters[i]->getCenter(),SSTR("+"<<monsters[i]->getLevel()*3<<"xp"),1,font,sf::Color::Yellow,40);
            if(player.addExp(3*monsters[i]->getLevel())){
                particlesUI.addEmitter({500,200},20,{150,255},{150,255},{150,255});
                particlesUI.addEmitter({300,200},20,{150,255},{150,255},{150,255});
                particlesUI.addEmitter({700,200},20,{150,255},{150,255},{150,255});
                particlesUI.addTextEmitter({400,900},"LEVEL UP!",1,font,sf::Color::Yellow,60);
                playerLvl.setString(SSTR(player.getLevel()));
            }
            playerExpProgress.setString(SSTR(player.getExp())+"/"+SSTR(player.getExpRequired()));
            playerExpProgress.setPosition(500-(playerExpProgress.getGlobalBounds().width/2),950.f);
            monsters.erase(monsters.begin()+i);
        }

        }
    }

}
}
   for(int i=0; i<monsters.size(); i++){
    //monsters[i]->randomMove(elapsed);
    float dist=monsters[i]->getDistance(player);
    if(dist>2000){
        monsters.erase(monsters.begin()+i);
    } else{
    if(monsters[i]->makeDecision(elapsed,player)) particles.addTextEmitter(player.getCenter(),SSTR(monsters[i]->damage),1,font,sf::Color::Red,36);

    monsters[i]->update(elapsed);
    }
}

if(monsters.size()<20){
generateMonster();
}

player.update(elapsed);
particles.update(elapsed);
particlesHp.update(elapsed);
particlesMana.update(elapsed);
particlesUI.update(elapsed);
playerHp.setString(SSTR(FIXED_FLOAT(player.getHealth())));
playerHp.setPosition(200-(playerHp.getGlobalBounds().width/2),940.f);

playerMana.setString(SSTR(FIXED_FLOAT(player.getMana())));
playerMana.setPosition(800-(playerMana.getGlobalBounds().width/2),940.f);
stats[13].position.x=(player.getHealth()/player.getMaxHealth()*400);
stats[14].position.x=(player.getHealth()/player.getMaxHealth()*400);
if(player.getHealth()<player.getMaxHealth()) particlesHp.emitters[0].startPos={stats[13].position.x,950.f};

stats[16].position.x=(1000-player.getMana()/player.getMaxMana()*400);
stats[19].position.x=(1000-player.getMana()/player.getMaxMana()*400);
if(player.getMana()<player.getMaxMana()) particlesMana.emitters[0].startPos={stats[16].position.x-20.f,950.f};


}
void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const{
sf::VertexArray tmp(sf::Quads,36); //biomes near the player
for(int x=0; x<3; x++)
for(int y=0; y<3; y++){
auto& biome=gameMap[clamp(playerYmap-1+y,0,49)*50+clamp(playerXmap-1+x,0,49)];
    tmp[(y*3+x)*4].color=biome.color;
    tmp[(y*3+x)*4+1].color=biome.color;
    tmp[(y*3+x)*4+2].color=biome.color;
    tmp[(y*3+x)*4+3].color=biome.color;

    tmp[(y*3+x)*4].position=biome.position*3000.f;
    tmp[(y*3+x)*4+1].position=biome.position*3000.f+sf::Vector2f(3000.f,0.f);
    tmp[(y*3+x)*4+2].position=biome.position*3000.f+sf::Vector2f(3000.f,3000.f);
    tmp[(y*3+x)*4+3].position=biome.position*3000.f+sf::Vector2f(0.f,3000.f);
}

//std::cout<<gameMap[clamp(playerXmap,0,50),clamp(playerYmap,0,50)].position.x<<"player x "<<player.hitbox.left<<"\n";
target.draw(tmp);
for(int i=0; i<monsters.size(); i++){
target.draw(*monsters[i],states);
}
target.draw(player);
target.draw(particles);
for(auto& text : texts){
    target.draw(text);
}
target.setView(target.getDefaultView());
target.draw(stats);
target.draw(playerLvl);
target.draw(playerHp);
target.draw(playerMana);
target.draw(playerExpProgress);
if(player.getHealth()<player.getMaxHealth()) target.draw(particlesHp);
if(player.getMana()<player.getMaxMana()) target.draw(particlesMana);
target.draw(particlesUI);
if(isMapActive){
target.draw(actualMap);
target.draw(playerOnMap);
target.draw(mapBorder);
}
}
void Game::addText(std::string text, sf::Vector2f pos,  sf::Color color){
sf::Text t;
t.setFont(font);
t.setString(text);
t.setFillColor(color);
t.setPosition(pos);
texts.push_back(t);
}

void Game::addMonster(int id, sf::Vector2f pos){
switch(id){
case 0:
monsters.push_back(std::make_unique<Zombie>(pos));
break;
case 1:
monsters.push_back(std::make_unique<Skeleton>(pos));
break;
case 2:
monsters.push_back(std::make_unique<Ghost>(pos));
break;
case 3:
    monsters.push_back(std::make_unique<Demon>(pos));
break;
case 4:
    monsters.push_back(std::make_unique<GiantSpider>(pos));
break;
case 5:
   monsters.push_back(std::make_unique<Succubus>(pos));
break;
case 6:
    monsters.push_back(std::make_unique<Troll>(pos));
break;
case 7:
    monsters.push_back(std::make_unique<Giant>(pos));
break;
case 8:
    monsters.push_back(std::make_unique<ToxicLizard>(pos));
break;
case 9:
    monsters.push_back(std::make_unique<Vampire>(pos));
break;
default: std::cout<<"no monster found\n";break;
}
}
void Game::generateMonster(){
sf::Vector2f pos(randomize(player.getCenter().x-1000,2000),randomize(player.getCenter().y-1000,2000));

switch(getBiome(pos)){
case 0: //deadlands
    switch((int)randomize(0,4)){
    case 0: addMonster(0,pos);  break; //zombie
    case 1: addMonster(1,pos);  break; //skeleton
    case 2: addMonster(2,pos);  break; //ghost
    case 3: addMonster(9,pos);  break; //vampire
    }
break;
case 1: //plains
      switch((int)randomize(0,2)){
    case 0: addMonster(6,pos);  break; //troll
    case 1: addMonster(7,pos);  break; //giant
      }
break;
case 2: //toxic swamp
    switch((int)randomize(0,3)){
    case 0: addMonster(0,pos);  break; //zombie
    case 1: addMonster(4,pos);  break; //giant spider
    case 2: addMonster(8,pos);  break; //toxic lizard
    }
break;
case 3: //desert
      switch((int)randomize(0,2)){
        case 0: addMonster(1,pos); break; //skeleton
        case 1: addMonster(5,pos); break; //succubus
      }
break;
case 4: //fire realm
    switch((int)randomize(0,4)){
         case 0: addMonster(1,pos); break; //skeleton
        case 1: addMonster(5,pos); break; //succubus
        case 2: addMonster(3,pos); break; //demon
        case 3: addMonster(9,pos); break; //vampire
    }
break;
}
}

int Game::getBiome(sf::Vector2f pos){
int xMap=clamp(pos.x/3000.f,0,49);
int yMap=clamp(pos.y/3000.f,0,49);

auto value=noiseValues2d[yMap*50+xMap];
    if(value<=30) return 0; // deadlands
    else if(value>30&&value<60) return 1; //plains
    else if(value>60&&value<80) return 2; //toxic swamp
    else if(value>80&&value<100) return 3; //desert
    else if(value>=100) return 4; // fire realm
    else return -1;
}
void Game::statsSetup(){
stats=sf::VertexArray(sf::Quads,20);
playerLvl.setFont(font);
playerLvl.setString(SSTR(player.getLevel()));
playerLvl.setCharacterSize(50);
playerLvl.setPosition(1000/2-(playerLvl.getGlobalBounds().width/2),900.f);

playerExpProgress.setFont(font);
playerExpProgress.setString(SSTR(player.getExp())+"/"+SSTR(player.getExpRequired()));
playerExpProgress.setCharacterSize(48);
playerExpProgress.setPosition(500-(playerExpProgress.getGlobalBounds().width/2),950.f);

playerHp.setFont(font);
playerHp.setFillColor(sf::Color::White);
playerHp.setCharacterSize(50);

playerMana.setFont(font);
playerMana.setFillColor(sf::Color::White);
playerMana.setCharacterSize(50);
//background
stats[0].position={0,900};
stats[1].position={1000,900};
stats[2].position={1000,1000};
stats[3].position={0,1000};

stats[0].color=sf::Color(60,70,80);
stats[1].color=sf::Color(60,70,80);
stats[2].color=sf::Color(60,70,80);
stats[3].color=sf::Color(60,70,80);
//hp bar
stats[4].position={0,950};
stats[5].position={400,950};
stats[6].position={400,1000};
stats[7].position={0,1000};

stats[4].color=sf::Color(90,60,60);
stats[5].color=sf::Color(50,20,20);
stats[6].color=sf::Color(50,20,20);
stats[7].color=sf::Color(90,60,60);
//hp bar fill
stats[12].position={0,950};
stats[13].position={400,950};
stats[14].position={400,1000};
stats[15].position={000,1000};


stats[12].color=sf::Color(150,60,60);
stats[13].color=sf::Color(200,60,60);
stats[14].color=sf::Color(200,60,60);
stats[15].color=sf::Color(150,60,60);


//mana bar
stats[8].position={600,950};
stats[9].position={1000,950};
stats[10].position={1000,1000};
stats[11].position={600,1000};

stats[8].color=sf::Color(60,60,90);
stats[9].color=sf::Color(20,20,50);
stats[10].color=sf::Color(20,20,50);
stats[11].color=sf::Color(60,60,90);

//mana bar fill
stats[16].position={600,950};
stats[17].position={1000,950};
stats[18].position={1000,1000};
stats[19].position={600,1000};

stats[16].color=sf::Color(60,90,200);
stats[17].color=sf::Color(60,90,150);
stats[18].color=sf::Color(60,90,150);
stats[19].color=sf::Color(60,90,200);

particlesHp.addHealingEmitter({stats[16].position.x,915.f},5,sf::Color::Red,true,sf::seconds(1.5));
particlesMana.addMagicEmitter({stats[19].position.x,915.f},4,sf::Color::Blue,true,sf::seconds(1.5));
}
