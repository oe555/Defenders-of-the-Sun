#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

class Weapon{
private:
    std::string name;
    std::string description;
    int attackDice;
    int attackMultiplier;
    int attackBonus;
    int precisionBonus;

    // Things special about this weapon
    std::vector<std::string> features;
public:
    Weapon();
    Weapon(std::string name_, std::string description_, int attackDice_, int attackMultiplier_, int attackBonus_, int precisionBonus_, std::vector<std::string> features_);

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

    void addFeature(std::string feature);
    bool hasFeature(std::string feature);
};

#endif