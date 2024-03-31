#ifndef META_H
#define META_H

#include <string>
#include <vector>
#include "Companion.h"
#include "Journal.h"

class Meta{
private:
    int silver;
    int proteinShakes;
    int perception;
    int charisma;
    std::string characterName;
    std::string characterDeity;
    std::vector<Armor> armorInventory;
    std::vector<Weapon> weaponInventory;

    static const int storyVarCount = 3;
    bool storyVariables[storyVarCount];
public:
    Journal journal;
    std::vector<Companion> companions;
    Meta();

    std::string getCharName();
    std::string getCharDeity();

    int getSilver();
    void gainSilver(int amount);
    bool spendSilver(int amount); // Returns false if there is not enough silver

    int getProteinShakes();
    void gainProteinShake();
    // Returns false if there are not enough protein shakes
    bool drinkProteinShake();

    
    void addCompanion(Companion companion);
    void removeCompanion(std::string name);
    void shuffleCompanions();

    int getPerception();
    int getCharisma();

    void addArmor(Armor armor);
    void addWeapon(Weapon weapon);

    void toggleStoryVariable(int index);
    bool getStoryVariable(int index);
};

#endif