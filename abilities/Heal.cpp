#include "Heal.h"

Heal::Heal() : Ability("Holy Heal", "hbl", 20, LIGHT, 2){}

bool Heal::effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles){
if(caster.getMana()>=manaCost){
caster.addHealth(spellPower*5+10);
particles.addEmitter(caster.getCenter(),15,{200,250},{200,250},{0,50});
sf::FloatRect attackRange(caster.hitbox.left-100.f,caster.hitbox.top-100.f,200.f, 200.f);
for(int i=0; i<monsters.size(); i++){
    if((monsters[i]->bodyType==UNDEAD || monsters[i]->bodyType==INFERNAL) && monsters[i]->hitbox.intersects(attackRange)){
    monsters[i]->removeHealth(spellPower*0.5+10);
    particles.addTextEmitter(sf::Vector2f(monsters[i]->hitbox.left,monsters[i]->hitbox.top),std::to_string(spellPower*0.5+10),1,sf::Color::White,36);
    }
}
caster.addMana(-manaCost);
return true;
}
else return false;
}
