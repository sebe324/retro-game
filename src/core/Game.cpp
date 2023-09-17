#include  "Game.h"

float randomize(int min, int n) {
    return (std::rand() % n) + min;
}

Game::Game(std::string texturePath, std::string fontPath,const sf::RenderWindow* w, sf::View* v) {
    if (!font.loadFromFile(fontPath)) {}
    if (!texture.loadFromFile(texturePath)) {}
    monsters.clear();
    texts.clear();
    projectiles.clear();
    particleSystem.clear();
    window = w;
    viewUI = v;
    player = std::make_unique<DarkKnight>("Player",sf::Vector2f(10000.f,10000.f));
    player->setLevel(10);
    playerOnMap = sf::VertexArray(sf::Quads, 4);
    ParticleSystem particlesWorld(sf::seconds(1.75), &font);
    ParticleSystem particlesHp(sf::seconds(1), &font);
    ParticleSystem particlesMana(sf::seconds(1), &font);
    ParticleSystem particlesUI(sf::seconds(1.75), &font);
    particleSystem.push_back(particlesWorld);
    particleSystem.push_back(particlesHp);
    particleSystem.push_back(particlesMana);
    particleSystem.push_back(particlesUI);
    statsSetup();
    playerXmap = (int)player->hitbox.left >> 12;
    playerYmap = (int)player->hitbox.top >> 12;
    mapBorder = sf::RectangleShape({200.f,200.f});
    mapBorder.setFillColor(sf::Color(0,0,0,0));
    mapBorder.setOutlineThickness(5.f);
    mapBorder.setPosition(5.f,5.f);
    mapBorder.setOutlineColor(sf::Color::Black);
}

void Game::changeMap(World &w) {
    gameWorld=World(w);
    actualMap = sf::VertexArray(sf::Quads, 10000);
    for(int y = 0; y < 50; y++) {
        for(int x = 0; x < 50; x++) {
            sf::Color color = World::biomeColors[gameWorld.getBiome(x,y)];
            actualMap[(y*50+x)*4+0].color = color;
            actualMap[(y*50+x)*4+1].color = color;
            actualMap[(y*50+x)*4+2].color = color;
            actualMap[(y*50+x)*4+3].color = color;

            actualMap[(y*50+x)*4+0].position  = sf::Vector2f(x,y)*4.f+sf::Vector2f(5.f,5.f);
            actualMap[(y*50+x)*4+1].position = sf::Vector2f(x,y)*4.f+sf::Vector2f(9.f,5.f);
            actualMap[(y*50+x)*4+2].position = sf::Vector2f(x,y)*4.f+sf::Vector2f(9.f,9.f);
            actualMap[(y*50+x)*4+3].position = sf::Vector2f(x,y)*4.f+sf::Vector2f(5.f,9.f);
        }
    }
    std::cout<<"print statements >>>>>>> debugger";
    updateMap();
}

//Update the small map in the top left corner

void Game::updateMap() {
    playerXmap = (int)player->hitbox.left >> 12;
    playerYmap = (int)player->hitbox.top >> 12;
    sf::Vector2f temp(Utils::clamp(playerXmap,0,49),Utils::clamp(playerYmap,0,49));
    playerOnMap[0].color = sf::Color::Magenta;
    playerOnMap[1].color = sf::Color::Magenta;
    playerOnMap[2].color = sf::Color::Magenta;
    playerOnMap[3].color = sf::Color::Magenta;

    playerOnMap[0].position = temp*4.f+sf::Vector2f(5.f,5.f);
    playerOnMap[1].position = temp*4.f+sf::Vector2f(9.f,5.f);
    playerOnMap[2].position = temp*4.f+sf::Vector2f(9.f,9.f);
    playerOnMap[3].position = temp*4.f+sf::Vector2f(5.f,9.f);

    std::cout<<"updated map"<<std::endl;
}

void Game::update(sf::Time elapsed, sf::Vector2f globalPos) {
    if (paused) {
        return;
    }
    manageInput(elapsed,globalPos);
    std::cout<<"uga buga"<<std::endl;
    for(int i = projectiles.size(); i > 0; i--) {
        if (projectiles[i-1]->lifetime < sf::Time::Zero) 
            projectiles.erase(projectiles.begin()+i-1);
        else 
            projectiles[i-1]->update(elapsed,monsters,player,particleSystem);
    }
    for(int i = monsters.size(); i > 0; i--) {
        float dist = monsters[i-1]->getDistance(*player);
        if (dist > 2000) {
            monsters.erase(monsters.begin()+i-1);
        } else {
            if (monsters[i-1]->getHealth() <= 0) {
                player->addExp(3*monsters[i-1]->getLevel());
                particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(monsters[i-1]->bodyParts,monsters[i-1]->bodyPartsNumber);
                particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(monsters[i-1]->getCenter(),"+"+Utils::toString(monsters[i-1]->getLevel()*3)+"xp",1,sf::Color::Yellow,40);
                monsters.erase(monsters.begin()+i-1);
            }
            else {
                monsters[i-1]->update(elapsed);
                monsters[i-1]->makeDecision(elapsed,*player,projectiles);
            }
        }
    }
    std::cout<<"uga buga2"<<std::endl;
    playerExpProgress.setString(Utils::toString(player->getExp())+"/"+Utils::toString(player->getExpRequired()));
    playerExpProgress.setPosition(500-(playerExpProgress.getGlobalBounds().width/2),840.f);
    std::cout<<"uga buga2.25"<<std::endl;
    if (monsters.size() < 20) {
        generateMonster();
    }
    std::cout<<"uga buga2.5"<<std::endl;
    if (player->checkLevelUp()) {
        particleSystem[ParticlesGame::PARTICLES_UI].addEmitter({500,200},20,{150,255},{150,255},{150,255});
        particleSystem[ParticlesGame::PARTICLES_UI].addEmitter({300,200},20,{150,255},{150,255},{150,255});
        particleSystem[ParticlesGame::PARTICLES_UI].addEmitter({700,200},20,{150,255},{150,255},{150,255});
        particleSystem[ParticlesGame::PARTICLES_UI].addTextEmitter({400,900},"LEVEL UP!",1,sf::Color::Yellow,60);
        playerLvl.setString(Utils::toString(player->getLevel()));
    }
    std::cout<<"uga buga3"<<std::endl;
    player->update(elapsed,monsters);
    updateParticles(elapsed);
}
void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    std::cout<<"begin draw"<<std::endl;
    sf::VertexArray tmp(sf::Quads,36); // biomes near the player
    for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
            int tmpY=Utils::clamp(playerYmap-1+y,0,49);
            int tmpX=Utils::clamp(playerXmap-1+x,0,49);
            sf::Color color = World::biomeColors[gameWorld.getBiome(tmpX,tmpY)];
            tmp[(y*3+x)*4+0].color = color;
            tmp[(y*3+x)*4+1].color = color;
            tmp[(y*3+x)*4+2].color = color;
            tmp[(y*3+x)*4+3].color = color;

            tmp[(y*3+x)*4].position = sf::Vector2f(tmpX << 12, tmpY << 12);
            tmp[(y*3+x)*4+1].position = sf::Vector2f(tmpX << 12, tmpY << 12)+sf::Vector2f(4096,0);
            tmp[(y*3+x)*4+2].position = sf::Vector2f(tmpX << 12, tmpY << 12)+sf::Vector2f(4096,4096);
            tmp[(y*3+x)*4+3].position = sf::Vector2f(tmpX << 12, tmpY << 12)+sf::Vector2f(0,4096);
        }
    }
    target.draw(tmp);
    for(int i = 0; i < monsters.size(); i++) {
        target.draw(*monsters[i], states);
    }
    target.draw(*player);

    for(int i = 0; i < projectiles.size(); i++) {
        target.draw(*projectiles[i]);
    }
    target.draw(particleSystem[ParticlesGame::PARTICLES_WORLD]);
    for(auto& text : texts) {
        target.draw(text);
    }
    target.setView(*viewUI);
    target.draw(stats);
    target.draw(playerLvl);
    target.draw(playerHp);
    target.draw(playerMana);
    target.draw(playerExpProgress);
    if (player->getHealth() < player->getMaxHealth()) 
        target.draw(particleSystem[ParticlesGame::PARTICLES_HP]);
    if (player->getMana() < player->getMaxMana()) 
        target.draw(particleSystem[ParticlesGame::PARTICLES_MANA]);
    target.draw(particleSystem[ParticlesGame::PARTICLES_UI]);
    if (isMapActive) {
        target.draw(actualMap);
        target.draw(playerOnMap);
        target.draw(mapBorder);
    }
}

void Game::addText(std::string text, sf::Vector2f pos,  sf::Color color) {
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setFillColor(color);
    t.setPosition(pos);
    texts.push_back(t);
}

void Game::addMonster(int id, sf::Vector2f pos) {
    switch(id) {
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
        default:
            std::cout << "no monster found\n";
            break;
    }
}
void Game::generateMonster() {
    sf::Vector2f pos(randomize(player->getCenter().x - 1000, 2000), randomize(player->getCenter().y - 1000, 2000));

    switch(getBiome(pos)) {
        case DEADLANDS:
            switch((int)randomize(0,4)) {
                case 0: addMonster(0,pos);  break; //zombie
                case 1: addMonster(1,pos);  break; //skeleton
                case 2: addMonster(2,pos);  break; //ghost
                case 3: addMonster(9,pos);  break; //vampire
            }
            break;
        case PLAINS:
            switch((int)randomize(0,2)) {
                case 0: addMonster(6,pos);  break; //troll
                case 1: addMonster(7,pos);  break; //giant
            }
            break;
        case TOXIC_SWAMP:
            switch((int)randomize(0,3)) {
                case 0: addMonster(0,pos);  break; //zombie
                case 1: addMonster(4,pos);  break; //giant spider
                case 2: addMonster(8,pos);  break; //toxic lizard
            }
            break;
        case DESERT:
            switch((int)randomize(0,2)) {
                case 0: addMonster(1,pos); break; //skeleton
                case 1: addMonster(5,pos); break; //succubus
            }
            break;
        case FIRE_REALM:
            switch((int)randomize(0,4)) {
                case 0: addMonster(1,pos); break; //skeleton
                case 1: addMonster(5,pos); break; //succubus
                case 2: addMonster(3,pos); break; //demon
                case 3: addMonster(9,pos); break; //vampire
            }
            break;
    }
}

int Game::getBiome(sf::Vector2f pos) {
    std::cout<<"huj0"<<std::endl;
    int xMap = Utils::clamp((int)pos.x >> 12, 0, 49);
    int yMap = Utils::clamp((int)pos.y >> 12, 0, 49);
    std::cout<<"huj"<<std::endl;
    return gameWorld.getBiome(xMap,yMap);
}

void Game::updateParticles(sf::Time& elapsed) {
    for(auto& ps : particleSystem) 
        ps.update(elapsed);
    playerHp.setString(Utils::toString(player->getHealth(), 1));
    playerHp.setPosition(200 - (playerHp.getGlobalBounds().width / 2), 940.f);

    playerMana.setString(Utils::toString(player->getMana(), 1));
    playerMana.setPosition(800 - (playerMana.getGlobalBounds().width / 2), 940.f);
    stats[13].position.x = (player->getHealth() / player->getMaxHealth() * 400);
    stats[14].position.x = (player->getHealth() / player->getMaxHealth() * 400);
    if (player->getHealth() < player->getMaxHealth()) 
        particleSystem[ParticlesGame::PARTICLES_HP].emitters[0].startPos = {stats[13].position.x, 950.f};
    stats[16].position.x = (1000 - player->getMana() / player->getMaxMana() * 400);
    stats[19].position.x = (1000 - player->getMana() / player->getMaxMana() * 400);
    if (player->getMana() < player->getMaxMana()) 
        particleSystem[ParticlesGame::PARTICLES_MANA].emitters[0].startPos = {stats[16].position.x - 20.f, 950.f};

    float targetExp = (float)player->getExp() / player->getExpRequired() * 1000;
    if (abs(targetExp - stats[25].position.x) <= 5)
        return;
    if (stats[26].position.x < targetExp) {
        stats[26].position.x += targetExp / 2.f * elapsed.asSeconds();
        stats[25].position.x += targetExp / 2.f * elapsed.asSeconds();
    } else {
        stats[26].position.x = 0;
        stats[25].position.x = 0;
    }
}

void Game::manageInput(sf::Time& elapsed, const sf::Vector2f& globalPos){
       if (sf::Keyboard::isKeyPressed(player->keyUp))
        player->moveUp(elapsed); 
    if (sf::Keyboard::isKeyPressed(player->keyDown))
        player->moveDown(elapsed); 
    if (sf::Keyboard::isKeyPressed(player->keyLeft))
        player->moveLeft(elapsed); 
    if (sf::Keyboard::isKeyPressed(player->keyRight))
        player->moveRight(elapsed); 
    updateMap();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        player->ability1(monsters, particleSystem, projectiles, globalPos);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        player->ability2(monsters, particleSystem, projectiles, globalPos);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        player->ability3(monsters, particleSystem, projectiles, globalPos);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) 
        isMapActive = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) 
        isMapActive = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
        player->attack(projectiles, globalPos, elapsed);
    
}
void Game::statsSetup() {
    stats = sf::VertexArray(sf::Quads, 28);
    playerLvl.setFont(font);
    playerLvl.setString(Utils::toString(player->getLevel()));
    playerLvl.setCharacterSize(50);
    playerLvl.setPosition(1000 / 2 - (playerLvl.getGlobalBounds().width / 2), 900.f);

    playerExpProgress.setFont(font);
    playerExpProgress.setString(Utils::toString(player->getExp())+"/"+Utils::toString(player->getExpRequired()));
    playerExpProgress.setCharacterSize(48);
    playerExpProgress.setPosition(500-(playerExpProgress.getGlobalBounds().width/2),840.f);

    playerHp.setFont(font);
    playerHp.setFillColor(sf::Color::White);
    playerHp.setCharacterSize(50);

    playerMana.setFont(font);
    playerMana.setFillColor(sf::Color::White);
    playerMana.setCharacterSize(50);
    //background
    stats[0].position = {0,900};
    stats[1].position = {1000,900};
    stats[2].position = {1000,1000};
    stats[3].position = {0,1000};

    stats[0].color = sf::Color(60,70,80);
    stats[1].color = sf::Color(60,70,80);
    stats[2].color = sf::Color(60,70,80);
    stats[3].color = sf::Color(60,70,80);
    //hp bar
    stats[4].position = {0,950};
    stats[5].position = {400,950};
    stats[6].position = {400,1000};
    stats[7].position = {0,1000};

    stats[4].color = sf::Color(90,60,60);
    stats[5].color = sf::Color(50,20,20);
    stats[6].color = sf::Color(50,20,20);
    stats[7].color = sf::Color(90,60,60);
    //hp bar fill
    stats[12].position = {0,950};
    stats[13].position = {400,950};
    stats[14].position = {400,1000};
    stats[15].position = {000,1000};


    stats[12].color = sf::Color(150,60,60);
    stats[13].color = sf::Color(200,60,60);
    stats[14].color = sf::Color(200,60,60);
    stats[15].color = sf::Color(150,60,60);


    //mana bar
    stats[8].position = {600,950};
    stats[9].position = {1000,950};
    stats[10].position = {1000,1000};
    stats[11].position = {600,1000};

    stats[8].color = sf::Color(60,60,90);
    stats[9].color = sf::Color(20,20,50);
    stats[10].color = sf::Color(20,20,50);
    stats[11].color = sf::Color(60,60,90);

    //mana bar fill
    stats[16].position = {600,950};
    stats[17].position = {1000,950};
    stats[18].position = {1000,1000};
    stats[19].position = {600,1000};

    stats[16].color = sf::Color(60,90,200);
    stats[17].color = sf::Color(60,90,150);
    stats[18].color = sf::Color(60,90,150);
    stats[19].color = sf::Color(60,90,200);

    // xp bar

    stats[20].position = {0.f,850.f};
    stats[21].position = {1000.f,850.f};
    stats[22].position = {1000.f,900.f};
    stats[23].position = {0.f,900.f};

    stats[20].color = sf::Color(40,40,40);
    stats[21].color = sf::Color(40,40,40);
    stats[22].color = sf::Color(40,40,40);
    stats[23].color = sf::Color(40,40,40);

    // xp bar fill

    stats[24].position = {0.f,850.f};
    stats[25].position = {1000.f,850.f};
    stats[26].position = {1000.f,900.f};
    stats[27].position = {0.f,900.f};

    stats[24].color = sf::Color(50,200,50);
    stats[25].color = sf::Color(50,200,50);
    stats[26].color = sf::Color(50,200,50);
    stats[27].color = sf::Color(50,200,50);

    particleSystem[ParticlesGame::PARTICLES_HP].addHealingEmitter({stats[16].position.x,915.f},5,sf::Color::Red,true,sf::seconds(1.5));
    particleSystem[ParticlesGame::PARTICLES_MANA].addMagicEmitter({stats[19].position.x,915.f},4,sf::Color::Blue,true,sf::seconds(1.5));
}

void Game::changePlayerClass(int playerClass) {
    switch(playerClass) {
        case DARK_KNIGHT:
            player = std::make_unique<DarkKnight>("Player",sf::Vector2f(10000.f,10000.f));
            break;
        case ARCHER:
            player = std::make_unique<Archer>("Player",sf::Vector2f(10000.f,10000.f));
            break;
        case PALADIN:
            player = std::make_unique<Paladin>("Player",sf::Vector2f(10000.f,10000.f));
            break;
        case ELEMAGE:
            player = std::make_unique<ElementMage>("Player",sf::Vector2f(10000.f,10000.f));
            break;
        default:
            //default class
            player = std::make_unique<DarkKnight>("Player",sf::Vector2f(10000.f,10000.f));
            break;
    }
    player->setLevel(10);
}

// Updates the current game to new settings
void Game::updateSettings(Settings& new_settings) {

    // For now, the only setting that may require updating
    player->movementWSAD(new_settings.WSAD);
}

void Game::reset(){
 monsters.clear();
    texts.clear();
    projectiles.clear();
    particleSystem.clear();
  ParticleSystem particlesWorld(sf::seconds(1.75), &font);
    ParticleSystem particlesHp(sf::seconds(1), &font);
    ParticleSystem particlesMana(sf::seconds(1), &font);
    ParticleSystem particlesUI(sf::seconds(1.75), &font);
    particleSystem.push_back(particlesWorld);
    particleSystem.push_back(particlesHp);
    particleSystem.push_back(particlesMana);
    particleSystem.push_back(particlesUI);
    statsSetup();      
}