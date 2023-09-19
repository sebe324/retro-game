#include "particleSystem.h"

ParticleSystem::ParticleSystem(sf::Time mt, sf::Font* f) {
    maxTime = mt;
    font = f;
}

ParticleSystem::ParticleSystem() {}

Emitter::Emitter(int a, 
                int b, 
                sf::Vector2f pos, 
                sf::Vector2f x, 
                sf::Vector2f y, 
                sf::Time rd, 
                sf::Time tl, 
                sf::VertexArray v, 
                bool rep) 
{
    amount = a;
    n = b;
    startPos = pos;
    velX = x;
    velY = y;
    resetDelay = rd;
    timeLeft = tl;
    vertices = v;
    repeat = rep;
}



void ParticleSystem::addTextEmitter(sf::Vector2f vPos, 
                                    std::string s, 
                                    int amount, 
                                    sf::Color color, 
                                    int charsize) 
{
    TextEmitter te;
    te.timeLeft=maxTime;
    for (int i=0; i<amount; i++) {
        sf::Text t;
        t.setFont(*font);
        t.setPosition(vPos);
        t.setString(s);
        t.setFillColor(color);
        t.setCharacterSize(charsize);
        te.texts.push_back(t);
        te.speed.push_back({randomize(-20,20),randomize(-50.f,-30.f)});
    }
    textEmitters.push_back(te);
}
void ParticleSystem::addEmitter(sf::Vector2f vPos, 
                                int amount, 
                                sf::Vector2i r, 
                                sf::Vector2i g,
                                sf::Vector2i b, 
                                bool rep, 
                                sf::Time rd) 
{
    Emitter emitter(amount,4,vPos,{-100.f,100.f},{-100.f,100.f},rd,maxTime,sf::VertexArray(sf::Quads,amount*4),rep);
    for (int i=0; i<amount; i++) {
        emitter.vertices[i*4].position=vPos;
        emitter.vertices[i*4+1].position=vPos+sf::Vector2f(20.f,0.f);
        emitter.vertices[i*4+2].position=vPos+sf::Vector2f(20.f,20.f);
        emitter.vertices[i*4+3].position=vPos+sf::Vector2f(0.f,20.f);
        sf::Color tmp(randomize(r.x,r.y),randomize(g.x,g.y),randomize(b.x,b.y));
        emitter.vertices[i*4].color=tmp;
        emitter.vertices[i*4+1].color=tmp;
        emitter.vertices[i*4+2].color=tmp;
        emitter.vertices[i*4+3].color=tmp;

        emitter.startPosOffset.push_back(sf::Vector2f(0.f,0.f));
        emitter.startPosOffset.push_back(sf::Vector2f(20.f,0.f));
        emitter.startPosOffset.push_back(sf::Vector2f(20.f,20.f));
        emitter.startPosOffset.push_back(sf::Vector2f(0.f,20.f));

        emitter.speed.push_back({randomize(emitter.velX.x,emitter.velX.y),randomize(emitter.velY.x,emitter.velY.y)});
    }

    emitters.push_back(emitter);
}

void ParticleSystem::addEmitter(sf::VertexArray vArray, 
                                int amount, 
                                bool rep,
                                sf::Time rd) 
{
    Emitter emitter(amount,4,vArray[0].position,{-50.f,50.f},{-50.f,50.f},rd,maxTime,vArray,rep);
    for (int i = 0; i < amount; i++) {
        emitter.speed.push_back({randomize(emitter.velX.x,emitter.velX.y),randomize(emitter.velY.x,emitter.velY.y)});
    }
    emitters.push_back(emitter);
}

void ParticleSystem::addHealingEmitter(sf::Vector2f vPos, 
                                        int amount, 
                                        sf::Color color, 
                                        bool rep, 
                                        sf::Time rd) 
{
    Emitter emitter(amount,8,vPos,{20.f,50.f},{-30.f,30.f},rd,maxTime,sf::VertexArray(sf::Quads,amount*8),rep);

    for (int i = 0; i < amount; i++) {
        emitter.vertices[i*8].position=vPos;
        emitter.vertices[i*8+1].position=vPos+sf::Vector2f(8.f,0.f);
        emitter.vertices[i*8+2].position=vPos+sf::Vector2f(8.f,20.f);
        emitter.vertices[i*8+3].position=vPos+sf::Vector2f(0.f,20.f);

        emitter.vertices[i*8+4].position=vPos+sf::Vector2f(-5.f,6.f);
        emitter.vertices[i*8+5].position=vPos+sf::Vector2f(13.f,6.f);
        emitter.vertices[i*8+6].position=vPos+sf::Vector2f(13.f,14.f);
        emitter.vertices[i*8+7].position=vPos+sf::Vector2f(-5.f,14.f);

        emitter.vertices[i*8].color=color;
        emitter.vertices[i*8+1].color=color;
        emitter.vertices[i*8+2].color=color;
        emitter.vertices[i*8+3].color=color;
        emitter.vertices[i*8+4].color=color;
        emitter.vertices[i*8+5].color=color;
        emitter.vertices[i*8+6].color=color;
        emitter.vertices[i*8+7].color=color;

        emitter.startPosOffset.push_back(sf::Vector2f(0.f,0.f));
        emitter.startPosOffset.push_back(sf::Vector2f(8.f,0.f));
        emitter.startPosOffset.push_back(sf::Vector2f(8.f,20.f));
        emitter.startPosOffset.push_back(sf::Vector2f(0.f,20.f));
        emitter.startPosOffset.push_back(sf::Vector2f(-5.f,6.f));
        emitter.startPosOffset.push_back(sf::Vector2f(13.f,6.f));
        emitter.startPosOffset.push_back(sf::Vector2f(13.f,14.f));
        emitter.startPosOffset.push_back(sf::Vector2f(-5.f,14.f));

        emitter.speed.push_back({randomize(emitter.velX.x,emitter.velX.y),randomize(emitter.velY.x,emitter.velY.y)});
    }

    emitters.push_back(emitter);
}

void ParticleSystem::addMagicEmitter(sf::Vector2f vPos, 
                                        int amount, 
                                        sf::Color color, 
                                        bool rep, 
                                        sf::Time rd) 
{
    Emitter emitter(amount,4,vPos,{-20.f,-50.f},{-30.f,30.f},rd,maxTime,sf::VertexArray(sf::Quads,amount*4),rep);

    for (int i = 0; i < amount; i++) {
        emitter.vertices[i*4].position=vPos+sf::Vector2f(randomize(-4,8),randomize(-4,8));
        emitter.vertices[i*4+1].position=vPos+sf::Vector2f(15.f,0.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8));
        emitter.vertices[i*4+2].position=vPos+sf::Vector2f(15.f,15.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8));
        emitter.vertices[i*4+3].position=vPos+sf::Vector2f(0.f,15.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8));

        emitter.startPosOffset.push_back(sf::Vector2f(0.f,0.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8)));
        emitter.startPosOffset.push_back(sf::Vector2f(15.f,0.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8)));
        emitter.startPosOffset.push_back(sf::Vector2f(15.f,15.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8)));
        emitter.startPosOffset.push_back(sf::Vector2f(0.f,15.f)+sf::Vector2f(randomize(-4,8),randomize(-4,8)));

        emitter.vertices[i*4].color=color;
        emitter.vertices[i*4+1].color=color;
        emitter.vertices[i*4+2].color=color;
        emitter.vertices[i*4+3].color=color;
        emitter.speed.push_back({randomize(emitter.velX.x,emitter.velX.y),randomize(emitter.velY.x,emitter.velY.y)});
    }
    emitters.push_back(emitter);
}


void ParticleSystem::update(sf::Time elapsed) {
    for (int i = 0; i < emitters.size(); i++) {
        emitters[i].timeLeft -= elapsed;
        if (emitters[i].timeLeft <= sf::Time::Zero && !emitters[i].repeat) {
            emitters.erase(emitters.begin()+i);
        }
        else if (emitters[i].timeLeft <= sf::Time::Zero - emitters[i].resetDelay && emitters[i].repeat) {
            emitters[i].timeLeft = maxTime;
        }
        else if (emitters[i].timeLeft <= sf::Time::Zero && emitters[i].repeat) {
            emitters[i].speed.clear();
            for (int j = 0; j < emitters[i].amount; j++) {
                for (int k = 0; k < emitters[i].n; k++) {
                    emitters[i].vertices[j*emitters[i].n+k].position=emitters[i].startPos+emitters[i].startPosOffset[j*emitters[i].n+k];
                }
                emitters[i].speed.push_back({randomize(emitters[i].velX.x,emitters[i].velX.y),randomize(emitters[i].velY.x,emitters[i].velY.y)});
            }
        }
        else {
            float fraction = (emitters[i].timeLeft / maxTime);
            for (int j = 0; j < emitters[i].amount; j++) {
                for (int k = 0; k < emitters[i].n; k++) {
                    emitters[i].vertices[j*emitters[i].n+k].color.a=fraction*255;
                    emitters[i].vertices[j*emitters[i].n+k].position+={emitters[i].speed[j].x*elapsed.asSeconds(),emitters[i].speed[j].y*elapsed.asSeconds()};
                }
            }
        }
    }

    for (int i = 0; i < textEmitters.size(); i++) {
        textEmitters[i].timeLeft -= elapsed;
        if (textEmitters[i].timeLeft<=sf::Time::Zero) {
            textEmitters.erase(textEmitters.begin()+i);
            continue;
        }
        float fraction = (textEmitters[i].timeLeft / maxTime);
        for (int j = 0; j < textEmitters[i].texts.size(); j++) {
            sf::Color temp = textEmitters[i].texts[j].getFillColor();
            temp.a = fraction * 255;
            textEmitters[i].texts[j].setFillColor(temp);
            textEmitters[i].texts[j].setPosition(textEmitters[i].texts[j].getPosition()+textEmitters[i].speed[j]*elapsed.asSeconds());
        }
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < emitters.size(); i++) {
        target.draw(emitters[i].vertices,states);
    }
    for (int i = 0; i < textEmitters.size(); i++) {
        for (int j = 0; j < textEmitters[i].texts.size(); j++) {
            target.draw(textEmitters[i].texts[j],states);
        }
    }
}

float ParticleSystem::randomize(int min, int max) {
    return (std::rand() % (max - min)) + min;
}
