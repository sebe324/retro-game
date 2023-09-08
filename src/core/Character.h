#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include "../Utilities/Utils.h"
#include "../enums/BodyType.h"
#include "Unit.h"
#include "../Projectile/Projectile.h"
#include "../Projectile/Arrow.h"
#include "../Projectile/SwordSwing.h"

#include "../enums/ParticlesGame.h"
#include "../enums/DamageType.h"

class Character : public Unit {
    public:
        float damage=0;
        float lastAttackDamage=0;
        float attackSpeed=0;
        BodyType bodyType=LIVING;
        sf::Time attackDelay;
        Character(std::string n, float d, float as, float spd, int l, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={50.f,80.f});
        Character();

        void update(sf::Time elapsed);

        virtual void attack(std::vector<std::unique_ptr<Projectile> > &projectiles, sf::Vector2f mousePos, sf::Time elapsed);
        void regenerate(sf::Time elapsed);
        bool isDead();
        void setLevel(int n);
        void levelUp();

        void setHealth(float n);
        void addHealth(float n);
        virtual void removeHealth(float n, DamageType damageType, std::vector<ParticleSystem> &particleSystem);
        void setMaxHealth(float n);
        void addMaxHealth(float n);
        void setHealthRegen(float n);
        void setMana(float n);
        void addMana(float n);
        void removeMana(float n);
        void setMaxMana(float n);
        void addMaxMana(float n);
        void setManaRegen(float n);

        void setShield(float n);
        void addShield(float n);
        void removeShield(float n);

        void setMaxShield(float n);
        void addMaxShield(float n);

        int getLevel() const;

        float getHealth() const;
        float getMaxHealth() const;
        float getHealthRegen() const;
        float getMana() const;
        float getMaxMana() const;
        float getManaRegen() const;

        float getShield() const;
        float getMaxShield() const;

        int getId() const;

        //Damage multiplier based on damage types.
        //Some characters will have a higher resistance for fire damage, some will be immune to it
        //For example infernal enemies will receive less damage from fire
        //Order is the same as in enums/DamageType.h - LIGHT, DARKNESS, EARTH, AIR, FIRE, WATER, PHYSIC, TRUE
        float damageMultiplier[8]={1,1,1,1,1,1,1,1};

    protected:
        int level=0;
    private:

        float health=0;
        float maxHealth=0;
        float healthRegen=0;

        float mana=0;
        float maxMana=0;
        float manaRegen=0;

        float shield=0;
        float maxShield=0;
        int id;
        static int characterCount;

};

#endif // CHARACTER_H
