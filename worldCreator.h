#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H


#include "Button.h"
#include "noise/perlinNoise.h"

#include <iomanip>
#include "Utilities/Utils.h"

class WorldCreator : public sf::Drawable{
public:

    int octaves=6;
    float bias=2.f;
    uint32_t seed;

    int playerClass=0;
    Button bIncreaseOctaves;
    Button bDecreaseOctaves;

    Button bIncreaseBias;
    Button bDecreaseBias;

    Button bRandomizeSeed;

    Button bChangeClass;

    Button bStartGame;

    Button bGoBack;
    WorldCreator();
    WorldCreator(sf::Font& font);

    void update(sf::Vector2f pos);
    void checkClick(sf::Vector2f pos);
    void clearVectors();
private:
    sf::Text biasText;
    sf::Text octavesText;
    sf::Text seedText;
    sf::Text classText;

    sf::Text titleText;


    sf::Text seedLabel;
    sf::Text biasLabel;
    sf::Text octavesLabel;
    void changeBias(float amount);
    void changeOctaves(int amount);

    void randomizeSeed();
    void changeClass();
    void updateMap();
    Rnd rnd;
    std::vector<float> randomValues2d;
    std::vector<float> noiseValues2d;
    sf::VertexArray gameMap;

    sf::RectangleShape background;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // WORLDCREATOR_H
