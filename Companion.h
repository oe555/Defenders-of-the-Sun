#ifndef COMPANION_H
#define COMPANION_H

#include <string>
#include <vector>
#include "Armor.h"
#include "Weapon.h"

class Companion{
private:
    std::string name;
    std::string diety;
    // Type is the class (Barbarian, Raven, Cleric, etc)
    std::string type;
    // This is the list of things the companion can do in battle
    std::vector<std::string> actions;
    // Health is set to max health at the start of every battle
    int maxHealth;
    int health;
    // How likely it is to hit someone (based on a d10 roll)
    int defense;
    int level;

    // STATUS EFFECTS (handled in encounter code)
    bool hiding;

    Weapon weapon;
    Armor armor;
public:
    Companion(std::string name_, std::string type_, std::string diety_);

    std::string getName();
    void setName(std::string name_);

    // Returns the class of the companion as a string
    std::string getType();
    void setType(std::string type_);

    std::string getDiety();
    void setDiety(std::string diety_);

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