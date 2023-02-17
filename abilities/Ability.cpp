#include "Ability.h"

Ability::Ability(std::string n, std::string c, int mcost, MagicBranch mbranch, int branchlvl){
name=n;
manaCost=mcost;
magicBranch=mbranch;
branchLevel=branchlvl;
combo=c;
}

bool Ability::effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles){
std::cout<<"elo";
}
