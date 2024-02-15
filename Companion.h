#ifndef COMPANION_H
#define COMPANION_H

#include <string>
#include <vector>
#include "Armor.h"
#include "Weapon.h"

class Companion{
private:
    std::string name;
    std::string type;
    std::vector<std::string> actions;
    int maxHealth;
    int health;
    int defense;
    int level;
    bool hiding;
    Weapon weapon;
    Armor armor;
public:
    Companion(std::string name_, std::string type_);

    std::string getName();
    void setName(std::string name_);

    std::string getType();
    void setType(std::string type_);

    std::vector<std::string> getActions();
    void addAction(std::string action_);
    void removeAction(std::string action_);

    int getMaxHealth();
    void setMaxHealth(int maxHealth_);

    int getHealth();
    void setHealth(int health_);

    int getDefense();
    void setDefense(int defense_);

    int getLevel();
    void levelUp();

    bool isHiding();
    void setHiding(bool hiding_);

    Weapon getWeapon();
    void setWeapon(Weapon weapon_);

    Armor getArmor();
    void setArmor(Armor armor_);

    int dealDamage();
    bool takeDamage(int damage);

    void getDetails();
};

#endif