#include  "Game.h"
float randomize(int min, int n){
return (std::rand()%n)+min;
}

Game::Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w){
if(!font.loadFromFile(fontPath)){}
if(!texture.loadFromFile(texturePath)){}
window=w;
player = Player("Player",1,2,100,10,{0.f,0.f},{50.f,90.f});
particles = ParticleSystem(sf::seconds(1.75));
particlesHp = ParticleSystem(sf::seconds(1));
particlesMana = ParticleSystem(sf::seconds(1));
particlesUI=ParticleSystem(sf::seconds(1.75));

for(int i=0; i<10; i++){
addMonster(randomize(0,10),sf::Vector2f(randomize(-500,1000),randomize(-500,1000)));
}
statsSetup();

}
void Game::update(sf::Time elapsed){
if(sf::Keyboard::isKeyPressed(player.keyUp)) player.moveUp(elapsed);
if(sf::Keyboard::isKeyPressed(player.keyDown)) player.moveDown(elapsed);
if(sf::Keyboard::isKeyPressed(player.keyLeft)) player.moveLeft(elapsed);
if(sf::Keyboard::isKeyPressed(player.keyRight)) player.moveRight(elapsed);
if(sf::Keyboard::isKeyPressed(player.keyRightAttack)){
   for(int i=0; i<monsters.size(); i++){
    if(player.hitbox.intersects(monsters[i]->hitbox)){
        monsters[i]->wakeUp();
        if(player.attack(*monsters[i],elapsed)){
                particles.addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),SSTR(player.damage),1,font,sf::Color::White,36);
                if(monsters[i]->getHealth()<=0){
            particles.addEmitter(monsters[i]->bodyParts,monsters[i]->bodyPartsNumber);
            particles.addTextEmitter(monsters[i]->getCenter(),SSTR("+"<<monsters[i]->getLevel()*3<<"xp"),1,font,sf::Color::Yellow,40);
            if(player.addExp(50*monsters[i]->getLevel())){
                particlesUI.addEmitter({500,200},20,{150,255},{150,255},{150,255});
                particlesUI.addEmitter({300,200},20,{150,255},{150,255},{150,255});
                particlesUI.addEmitter({700,200},20,{150,255},{150,255},{150,255});
                particlesUI.addTextEmitter({400,900},"LEVEL UP!",1,font,sf::Color::Yellow,60);
                playerLvl.setString(SSTR(player.getLevel()));
            }
            std::cout<<player.getExp()<<"/"<<player.getExpRequired()<<"\n";
            monsters.erase(monsters.begin()+i);
        }
        }
    }

}
}
   for(int i=0; i<monsters.size(); i++){
    monsters[i]->randomMove(elapsed);
    monsters[i]->move();
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
if(player.getHealth()<player.getMaxHealth()) target.draw(particlesHp);
if(player.getMana()<player.getMaxMana()) target.draw(particlesMana);
target.draw(particlesUI);
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
}
}

void Game::statsSetup(){
stats=sf::VertexArray(sf::Quads,20);
playerLvl.setFont(font);
playerLvl.setString(SSTR(player.getLevel()));
playerLvl.setCharacterSize(50);
playerLvl.setPosition(1000/2-(playerLvl.getGlobalBounds().width/2),900.f);

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
