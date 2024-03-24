#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

class Enemy{
private:
    std::string name;
    int health;
    int defense; // Probability of missing / 10
    int attackDice;
    int attackMultiplier;
    int attackBonus;
    bool intelligent; // Determines whether the Enemy attacks a random companion or the lowest health companion

    std::vector<std::string> statusEffects;
public:
    Enemy(std::string name_, int health_, int defense_, int attackDice_, int attackMultiplier_, int attackBonus_, bool intelligent_);

    std::string getName();
    void setName(std::string name_);

    int getHealth();
    void setHealth(int health_);

    int getDefense();
    void setDefense(int defense_);

    int getAttackDice();
    void setAttackDice(int attackDice_);

    int getAttackMultiplier();
    void setAttackMultiplier(int attackMultiplier_);

    int getAttackBonus();
    void setAttackBonus(int attackBonus_);

    bool isIntelligent();
    void setIntelligent(bool intelligent_);

    int dealDamage();
    bool takeDamage(int damage, int precisionBonus); // Returns true if enemy dies

    void addStatusEffect(std::string effect);
    bool hasStatusEffect(std::string effect);
};

#endif