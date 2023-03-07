#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include "../Monster.h"
#include "../magicBranch.h"
#include <sstream>

class Ability{
public:
std::string name;
std::string combo;
int manaCost;
MagicBranch magicBranch;
int branchLevel;

Ability(std::string n, std::string c, int mcost, MagicBranch mbranch, int branchlvl);

virtual bool effect(Character& caster, std::vector<std::unique_ptr<Monster>>& monsters, int spellPower, ParticleSystem& particles);
};
#endif // ABILITY_H
