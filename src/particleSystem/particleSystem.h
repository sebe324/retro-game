#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

struct Emitter {
    bool repeat;
    int amount;
    int n;
    sf::Vector2f startPos;
    sf::Vector2f velX;
    sf::Vector2f velY;
    sf::Time resetDelay;
    sf::Time timeLeft;

    sf::VertexArray vertices;
    std::vector<sf::Vector2f> speed;
    std::vector<sf::Vector2f> startPosOffset;

    Emitter(int a, int b, sf::Vector2f pos, sf::Vector2f x, sf::Vector2f y, sf::Time rd, sf::Time tl, sf::VertexArray v, bool rep);
};
struct TextEmitter {
    sf::Time timeLeft;
    std::vector<sf::Text> texts;
    std::vector<sf::Vector2f> speed;
};
class ParticleSystem : public sf::Drawable {
    public:
        sf::Font* font;
        sf::Time maxTime;
        std::vector<Emitter> emitters;
        std::vector<TextEmitter> textEmitters;
        ParticleSystem(sf::Time mt, sf::Font* f);
        ParticleSystem();
        void update(sf::Time elapsed);

        void addEmitter(sf::Vector2f vPos, int amount, sf::Vector2i r={100,255},sf::Vector2i g={0,50},sf::Vector2i b={0,50}, bool rep=false,sf::Time rd=sf::Time::Zero);

        void addEmitter(sf::VertexArray vArray, int amount, bool rep=false, sf::Time rd=sf::Time::Zero);

        void addHealingEmitter(sf::Vector2f vPos,int amount, sf::Color color, bool rep=false, sf::Time rd=sf::Time::Zero);

        void addMagicEmitter(sf::Vector2f vPos, int amount, sf::Color color, bool rep=false, sf::Time rd=sf::Time::Zero);

        void addTextEmitter(sf::Vector2f vPos, std::string s, int amount, sf::Color color, int charsize=12);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        float randomize(int min, int n);

};
#endif // PARTICLEEMITTER_H
