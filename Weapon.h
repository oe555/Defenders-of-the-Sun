#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon{
private:
    std::string name;
    std::string description;
    int attackDice;
    int attackMultiplier;
    int attackBonus;
    int precisionBonus;
public:
    Weapon();
    Weapon(std::string name_, std::string description_, int attackDice_, int attackMultiplier_, int attackBonus_, int precisionBonus_);

    std::string getName();
    void setName(std::string name_);

    std::string getDescription();
    void setDescription(std::string description_);

    int getAttackDice();
    void setAttackDice(int attackDice_);

    int getAttackMultiplier();
    void setAttackMultiplier(int attackMultiplier_);

    int getAttackBonus();
    void setAttackBonus(int attackBonus_);

    int getPrecisionBonus();
    void setPrecisionBonus(int precisionBonus_);

    int dealDamage();
};

#endif