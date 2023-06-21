#include "worldCreator.h"

float round(float num, int precision)
{
    return floorf(num * pow(10.0f,precision) + .5f)/pow(10.0f,precision);
}

WorldCreator::WorldCreator(){}

WorldCreator::WorldCreator(sf::Font& font){

    gameMap=sf::VertexArray(sf::Quads, 50*50*4);
    randomValues2d=std::vector<float>(2500);

bIncreaseOctaves=Button("+",60,sf::Color::Black,{675.f,100.f},{75.f,75.f},sf::Color(39,174,96),font);
bDecreaseOctaves=Button("-",60,sf::Color::Black,{900.f,100.f},{75.f,75.f},sf::Color(192,57,43),font);

bIncreaseOctaves.hoverBodyColor=sf::Color(46,204,113);
bIncreaseOctaves.hoverContentColor=sf::Color::White;
bDecreaseOctaves.hoverBodyColor=sf::Color(231,76,60);
bDecreaseOctaves.hoverContentColor=sf::Color::White;

octavesText.setFont(font);
octavesText.setString(std::to_string(octaves));
octavesText.setCharacterSize(90);
octavesText.setPosition(825.f-octavesText.getGlobalBounds().width/2,70.f);

octavesLabel.setFont(font);
octavesLabel.setString("Detail");
octavesLabel.setCharacterSize(60);
octavesLabel.setPosition(675.f,20.f);

bIncreaseBias=Button("+",60,sf::Color::Black,{675.f,250.f},{75.f,75.f},sf::Color(39,174,96),font);
bDecreaseBias=Button("-",60,sf::Color::Black,{900.f,250.f},{75.f,75.f},sf::Color(192,57,43),font);

bIncreaseBias.hoverBodyColor=sf::Color(46,204,113);
bIncreaseBias.hoverContentColor=sf::Color::White;

bDecreaseBias.hoverBodyColor=sf::Color(231,76,60);
bDecreaseBias.hoverContentColor=sf::Color::White;

biasText.setFont(font);
biasText.setString(Utils::toString(bias,1));
biasText.setCharacterSize(90);
biasText.setPosition(825.f-biasText.getGlobalBounds().width/2,220.f);

biasLabel.setFont(font);
biasLabel.setString("Bias");
biasLabel.setCharacterSize(60);
biasLabel.setPosition(675.f, 170.f);
bRandomizeSeed=Button("",50,sf::Color::Black,{675.f,500.f},{125.f,100.f},sf::Color(142,68,173),font);

bRandomizeSeed.hoverBodyColor=sf::Color(155,89,182);
bRandomizeSeed.hoverContentColor=sf::Color::White;

bConfirmSeed=Button("OK",50,sf::Color::Black,{850.f,500.f},{125.f,100.f},sf::Color(142,68,173),font);
bConfirmSeed.hoverBodyColor=sf::Color(155,89,182);
bConfirmSeed.hoverContentColor=sf::Color::White;

seedInput=Textbox("0000",font,{675.f,400.f},75,sf::Color::White,sf::Color(90,62,28));
seedInput.setMaxSize(6);
seedLabel.setFont(font);
seedLabel.setString("Seed");
seedLabel.setPosition(675.f, 335.f);
seedLabel.setCharacterSize(60);

bStartGame=Button("Start Game",50,sf::Color::Black,{675.f,800.f},{300.f,100.f},sf::Color(92,64,51),font);

bStartGame.hoverContentColor=sf::Color::White;
bChangeClass=Button("Dark Knight",50,sf::Color(20,20,20),{100.f,800.f},{400.f,100.f},sf::Color(92,64,51),font);
bChangeClass.hoverContentColor=sf::Color::White;

bGoBack=Button("Menu",50,sf::Color::Black,{675.f,675.f},{300.f,100.f},sf::Color(92,64,51),font);
bGoBack.hoverContentColor=sf::Color::White;

background=sf::RectangleShape({1000.f,1000.f});
background.setFillColor(sf::Color(130,102,68));
randomizeSeed();
updateMap();

if(!diceTexture.loadFromFile("dice.png")){
    //idk
}
diceSprite.setTexture(diceTexture);

diceSprite.setPosition({705.f,510.f});
diceSprite.setColor(sf::Color::Black);
}
void WorldCreator::update(sf::Vector2f pos){
bIncreaseOctaves.update(pos);
bDecreaseOctaves.update(pos);

bIncreaseBias.update(pos);
bDecreaseBias.update(pos);

bRandomizeSeed.update(pos);
bStartGame.update(pos);
bChangeClass.update(pos);
bGoBack.update(pos);
bConfirmSeed.update(pos);
if(bRandomizeSeed.contains(pos)){
    diceSprite.setColor(sf::Color::White);
}
else diceSprite.setColor(sf::Color::Black);
}
void WorldCreator::checkClick(sf::Vector2f pos){
if(bIncreaseOctaves.click(pos)) changeOctaves(1);
else if(bDecreaseOctaves.click(pos)) changeOctaves(-1);
else if(bIncreaseBias.click(pos)) changeBias(0.1f);
else if(bDecreaseBias.click(pos)) changeBias(-0.1f);
else if(bRandomizeSeed.click(pos)) randomizeSeed();
else if(bChangeClass.click(pos)) changeClass();
else if(bConfirmSeed.click(pos)) changeSeed(std::stoi(seedInput.getTextValue()));
else seedInput.isClicked(pos);
}
void WorldCreator::changeBias(float amount){
bias+=amount;
if(bias<0.2f) bias=0.2f;
else if(bias>5.f) bias=5.f;
biasText.setString(Utils::toString(bias,1));
biasText.setPosition(825.f-biasText.getGlobalBounds().width/2,220.f);
updateMap();
}

void WorldCreator::changeOctaves(int amount){
octaves+=amount;
if(octaves<1) octaves=1;
else if(octaves>6) octaves=6;
octavesText.setString(std::to_string(octaves));
octavesText.setPosition(825.f-octavesText.getGlobalBounds().width/2,70.f);
updateMap();
}

void WorldCreator::randomizeSeed(){
seed=(int)std::rand()%(10000)+1;
rnd.seed=seed;
for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
    randomValues2d[y*50+x]=rnd.rndInt(0,100);
}
seedInput.text.setString(std::to_string(seed));
updateMap();
}

void WorldCreator::changeClass(){
playerClass++;
if(playerClass>3) playerClass=0;

switch(playerClass){
case 0:
bChangeClass.content.setString("Dark Knight");
break;
case 1:
bChangeClass.content.setString("Archer");
break;
case 2:
bChangeClass.content.setString("Paladin");
break;
case 3:
bChangeClass.content.setString("EleMage");
break;
}
}

void WorldCreator::updateMap(){

noiseValues2d=rnd.perlin2d(randomValues2d,50,50,octaves,bias);

for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
    sf::Color color;
    auto value=noiseValues2d[y*50+x];
    if(value<=30) color=sf::Color(64,64,122);
    else if(value>30&&value<60) color=sf::Color(46, 113, 53);
    else if(value>=60&&value<80) color=sf::Color(116,146,76);
    else if(value>=80&&value<100) color=sf::Color(204,174,98);
    else if(value>=100) color=sf::Color(100,20,20);
    gameMap[(y*50+x)*4].color=color;
    gameMap[(y*50+x)*4].position={100.f+x*10.f,100.f+y*10.f};
    gameMap[(y*50+x)*4+1].color=color;
    gameMap[(y*50+x)*4+1].position={100.f+x*10.f+10.f,100.f+y*10.f};
    gameMap[(y*50+x)*4+2].color=color;
    gameMap[(y*50+x)*4+2].position={100.f+x*10.f+10.f,100.f+y*10.f+10.f};
    gameMap[(y*50+x)*4+3].color=color;
    gameMap[(y*50+x)*4+3].position={100.f+x*10.f,100.f+y*10.f+10.f};
}
}
void WorldCreator::draw(sf::RenderTarget& target, sf::RenderStates states) const{

target.draw(background);

target.draw(bIncreaseOctaves);
target.draw(bDecreaseOctaves);
target.draw(octavesText);
target.draw(octavesLabel);

target.draw(bIncreaseBias);
target.draw(bDecreaseBias);
target.draw(biasText);
target.draw(biasLabel);

target.draw(bRandomizeSeed);
target.draw(bConfirmSeed);
target.draw(seedInput);
target.draw(seedLabel);

target.draw(bChangeClass);
target.draw(classText);

target.draw(bStartGame);
target.draw(gameMap);

target.draw(bGoBack);
target.draw(diceSprite);
}
void WorldCreator::clearVectors(){
    std::vector<float> randomValues2d;
    std::vector<float> noiseValues2d;
    sf::VertexArray gameMap;
}

void WorldCreator::changeSeed(size_t s)
{
seed=s;
rnd.seed=s;
for(int x=0; x<50; x++)
for(int y=0; y<50; y++){
    randomValues2d[y*50+x]=rnd.rndInt(0,100);
}
seedInput.text.setString(std::to_string(seed));
updateMap();
}
