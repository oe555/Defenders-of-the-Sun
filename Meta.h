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
    int slightOfHand;
    int perception;
    int charisma;
public:
    Journal journal;
    std::vector<Companion> companions;
    Meta();

    int getSilver();
    void gainSilver(int amount);
    bool spendSilver(int amount); // Returns false if there is not enough silver

    int getProteinShakes();
    void gainProteinShake();
    bool drinkProteinShake();

    void addCompanion(Companion companion);
    void removeCompanion(std::string name);
    void shuffleCompanions();

    int getSlightOfHand();
    int getPerception();
    int getCharisma();
};

#endif