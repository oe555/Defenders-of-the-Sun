#ifndef ARMOR_H
#define ARMOR_H

#include <string>

class Armor{
private:
    std::string name;
    std::string description;
    int defenseBonus;
public:
    Armor();
    Armor(std::string name_, std::string description_, int defenseBonus_);

    std::string getName();
    void setName(std::string name_);

    std::string getDescription();
    void setDescription(std::string description_);

    int getDefenseBonus();
    void setDefenseBonus(int defenseBonus_);
};

#endif