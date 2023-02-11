#include "GiantSpider.h"

GiantSpider::GiantSpider(sf::Vector2f p) : Monster("Giant Spider",2,8,p,{88.f,45.f}){
createBodyPart({28.f,28.f},{0.f, 7.f}, sf::Color(47,54,64));
createBodyPart({60.f,35.f},{28.f,0.f},sf::Color(77,74,84));
createBodyPart({10.f,10.f},{28.f,35.f},sf::Color(77,74,84));
createBodyPart({10.f,10.f},{43.f,35.f},sf::Color(77,74,84));
createBodyPart({10.f,10.f},{58.f,35.f},sf::Color(77,74,84));
createBodyPart({10.f,10.f},{73.f,35.f},sf::Color(77,74,84));
createBodyPart({5.f,5.f},{5.f,12.f},sf::Color::Red);
createBodyPart({5.f,5.f},{15.f,12.f},sf::Color::Red);
createBodyPart({5.f,5.f},{5.f,22.f},sf::Color::Red);
}
