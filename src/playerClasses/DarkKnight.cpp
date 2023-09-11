#include "DarkKnight.h"
#include "../monsters/Monster.h"

// Dark Knight Constructor
DarkKnight::DarkKnight(std::string n, sf::Vector2f p) : Player(n,p,{50.f,90.f}) {
    createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(230,200,200));
    createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(48,59,107));
    createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(111,30,81));
    createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(111,30,81));
    createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(19,15,64));
    createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(19,15,64));
    createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(19,15,64));
    createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(19,15,64));

    ability1Time = sf::seconds(5);
    ability2Time = sf::seconds(10);
    ability3Time = sf::seconds(20);

    ability1Cost = 20.f;
    ability2Cost = 40.f;
    ability3Cost = 30.f;
}

// Function that turns Dark Knight into its original self
void DarkKnight::becomeNormal(std::vector<std::unique_ptr<Monster>>& monsters) {
    left = true;
    moveLeft(sf::seconds(1),0.1f);
    bodyParts.clear();
    createBodyPart({30.f,30.f},{10.f,0.f},sf::Color(230,200,200));
    createBodyPart({30.f,50.f},{10.f,30.f},sf::Color(48,59,107));
    createBodyPart({5.f,5.f},{15.f,10.f},sf::Color(111,30,81));
    createBodyPart({5.f,5.f},{25.f,10.f},sf::Color(111,30,81));
    createBodyPart({10.f,40.f},{0.f,30.f},sf::Color(19,15,64));
    createBodyPart({10.f,40.f},{40.f,30.f},sf::Color(19,15,64));
    createBodyPart({15.f,10.f},{6.f,80.f},sf::Color(19,15,64));
    createBodyPart({15.f,10.f},{29.f,80.f},sf::Color(19,15,64));
    batForm = false;
    ability3Cooldown = ability3Time;
    damage = damageTemporary;

    // Change enemy behavior to how it is normally
    for (int i = 0; i < monsters.size(); i++) {
        monsters[i]->attitude = monsters[i]->defaultAttitude;
    }
}

// Function that turns Dark Knight into its bat form
void DarkKnight::becomeBat(std::vector<std::unique_ptr<Monster>>& monsters) {
    moveRight(sf::seconds(1),0.1f);
    bodyParts.clear();
    createBodyPart({30.f,10.f},{0.f,0.f},sf::Color::Black);
    createBodyPart({45.f,15.f},{15.f,10.f},sf::Color::Black);
    createBodyPart({30.f,10.f},{45.f,0.f},sf::Color::Black);
    createBodyPart({10.f,10.f},{25.f,25.f},sf::Color::Black);
    createBodyPart({10.f,10.f},{40.f,25.f},sf::Color::Black);
    createBodyPart({5.f,5.f},{35.f,15.f},sf::Color(111,30,81));
    createBodyPart({5.f,5.f},{45.f,15.f},sf::Color(111,30,81));
    batForm = true;
    ability3Cooldown = sf::seconds(1);
    removeMana(ability3Cost);
    damageTemporary = damage;
    damage = 0.f;

    // Make enemies neutral to your presence
    for (int i = 0; i < monsters.size(); i++) {
        monsters[i]->attitude = Neutral;
    }
}


void DarkKnight::ability1(std::vector<std::unique_ptr<Monster>>& monsters, 
                            std::vector<ParticleSystem> &particleSystem,  
                            std::vector<std::unique_ptr<Projectile>> &projectiles, 
                            sf::Vector2f mousePos) {
    
    if (ability1Cooldown > sf::Time::Zero || getMana() < ability1Cost) {
        return;
    }
    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),15,{150,200},{0,50},{50,100});
    sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
    float healed=0;
    for (int i=0; i<monsters.size(); i++) {
        if (monsters[i]->hitbox.intersects(attackRange)) {
            monsters[i]->removeHealth(damage*0.5f+10, DARKNESS,particleSystem);
            addHealth(damage*0.25f+5);
            healed+=(damage*0.25f+5);
        }
    }
    if (healed>0) {
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(0.f,100.f),"+"+Utils::toString(healed,1)+"hp",1,sf::Color::Green,60);
    }
    removeMana(ability1Cost);
    ability1Cooldown=ability1Time;
}



void DarkKnight::ability2(std::vector<std::unique_ptr<Monster>>& monsters, 
                            std::vector<ParticleSystem> &particleSystem, 
                            std::vector<std::unique_ptr<Projectile>> &projectiles, 
                            sf::Vector2f mousePos) {
    if (ability2Cooldown > sf::Time::Zero || getMana() < ability2Cost) {
        return;
    }
    sf::FloatRect attackRange(hitbox.left-100.f,hitbox.top-100.f,200.f, 200.f);
    particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(), 15,{30,50},{30,50},{30,50});
    particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"FEAR THE DARK",1,sf::Color::Black,72);
    for (int i=0; i<monsters.size(); i++) {
        if (!monsters[i]->hitbox.intersects(attackRange) && monsters[i]->getLevel() >= level-5)
            continue;
        if (monsters[i]->bodyType==UNDEAD || monsters[i]->bodyType==INFERNAL) {
            monsters[i]->attitude=Neutral;
        }
        else if (monsters[i]->bodyType==LIVING) {
            monsters[i]->removeHealth(damage*0.3f+5, DARKNESS, particleSystem);
            monsters[i]->attitude=Cowardly;
        }
    }
    removeMana(ability2Cost);
    ability2Cooldown = ability2Time;
}


void DarkKnight::ability3(std::vector<std::unique_ptr<Monster>>& monsters, 
                            std::vector<ParticleSystem> &particleSystem,  
                            std::vector<std::unique_ptr<Projectile>> &projectiles, 
                            sf::Vector2f mousePos) {

    if (ability3Cooldown > sf::Time::Zero) {
        return;
    }

    if (batForm) {
        becomeNormal(monsters);

        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"POOF",1,sf::Color(90,90,90),72);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),20,{20,50},{20,50},{20,50});
    } else {
        if (getMana() < ability3Cost)
            return;

        becomeBat(monsters);

        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(getCenter()+sf::Vector2f(-100.f,-100.f),"POOF",1,sf::Color(90,90,90),72);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addEmitter(getCenter(),20,{20,50},{20,50},{20,50});
    }
}

void DarkKnight::update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>>& monsters) {
    regenerate(elapsed);
    attackDelay -= elapsed;
    ability1Cooldown -= elapsed;
    ability2Cooldown -= elapsed;
    ability3Cooldown -= elapsed;

    if (!batForm) {
        move();
        return;
    }
    // Drain mana if in batForm, switch to human form once mana reaches zero
    drainManaBat += elapsed.asSeconds();
    if (drainManaBat >= 1) {
        removeMana(10.f);
        drainManaBat = 0;
    }
    for (int i = 0; i < monsters.size(); i++) {
        monsters[i]->attitude = Neutral;
    }
    if (getMana() <= 0) {
        becomeNormal(monsters);
        setMana(0);
    }
    move();
}
