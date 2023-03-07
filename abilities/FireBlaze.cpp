#include "FireBlaze.h"

FireBlaze::FireBlaze() : Ability("FireBlaze", "fre",25,FIRE,1){}

bool FireBlaze::effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles){
if(caster.getMana()>=manaCost){
    caster.addMana(-manaCost);
    particles.addEmitter(caster.getCenter(),20);
    sf::FloatRect attackRange(caster.hitbox.left-200.f,caster.hitbox.top-200.f,400.f, 400.f);
    for(int i=0; i<monsters.size(); i++){
    if(monsters[i]->hitbox.intersects(attackRange) && monsters[i]->bodyType!=INFERNAL){
    monsters[i]->removeHealth(spellPower*3+20);
    particles.addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),std::to_string(spellPower*3+20),1,sf::Color::White,36);
    }
}
return true;
}
else return false;
}
