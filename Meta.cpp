#include "Meta.h"
#include <iostream>
#include <algorithm>

Meta::Meta(){
    silver = 0;
    proteinShakes = 1;
    std::cout << "Enter your character's name:\n";
    std::string charName;
    getline(std::cin, charName);
    characterName = charName;
    std::cout << "\nSelect a class by entering the corresponding number:\n";
    std::cout << "1) Barbarian\n";
    std::cout << "2) Wizard\n";
    std::cout << "3) Rogue\n";
    std::cout << "4) Druid\n";
    std::cout << "5) Necromancer\n";
    std::cout << "6) Monk\n";
    std::cout << "7) Cleric\n";
    std::cout << "8) Paladin\n";
    std::string charClass;
    std::string charClassInput;
    while(true){
        getline(std::cin, charClassInput);
        if(charClassInput == "1"){
            charClass = "Barbarian";
            break;
        }
        if(charClassInput == "2"){
            charClass = "Wizard";
            break;
        }
        if(charClassInput == "3"){
            charClass = "Rogue";
            break;
        }
        if(charClassInput == "4"){
            charClass = "Druid";
            break;
        }
        if(charClassInput == "5"){
            charClass = "Necromancer";
            break;
        }
        if(charClassInput == "6"){
            charClass = "Monk";
            break;
        }
        if(charClassInput == "7"){
            charClass = "Cleric";
            break;
        }
        if(charClassInput == "8"){
            charClass = "Paladin";
            break;
        }
        std::cout << "Input not recognized. Please try again.\n";
    }
    Companion player = Companion(charName, charClass);
    companions.push_back(player);
    slightOfHand = 0;
    if(charClass == "Rogue") slightOfHand += 2;
    if(charClass == "Monk") slightOfHand++;
    if(charClass == "Paladin") slightOfHand--;
    perception = 0;
    if(charClass == "Wizard") perception++;
    if(charClass == "Rogue") perception++;
    if(charClass == "Druid") perception++;
    if(charClass == "Necromancer") perception++;
    if(charClass == "Monk") perception++;
    if(charClass == "Cleric") perception++;
    if(charClass == "Paladin") perception--;
    charisma = 0;
    if(charClass == "Barbarian") charisma--;
    if(charClass == "Wizard") charisma++;
    if(charClass == "Rogue") charisma++;
    journal = Journal();
}

std::string Meta::getCharName(){
    return characterName;
}

int Meta::getSilver(){
    return silver;
}

void Meta::gainSilver(int amount){
    silver += amount;
}

bool Meta::spendSilver(int amount){
    if(silver - amount < 0) return false;
    silver -= amount;
    return true;
}

int Meta::getProteinShakes(){
    return proteinShakes;
}

void Meta::gainProteinShake(){
    proteinShakes++;
}

// Returns false if there are not enough protein shakes
bool Meta::drinkProteinShake(){
    if(proteinShakes == 0) return false;
    proteinShakes--;
    return true;
}

void Meta::addCompanion(Companion companion){
    companions.push_back(companion);
}

void Meta::removeCompanion(std::string name){
    for(int i = 0; i < (int)companions.size(); i++){
        if(companions[i].getName() == name){
            companions.erase(companions.begin() + i);
        }
    }
}

void Meta::shuffleCompanions(){
    std::random_shuffle(companions.begin(), companions.end());
}

int Meta::getSlightOfHand(){
    return slightOfHand;
}

int Meta::getPerception(){
    return perception;
}

int Meta::getCharisma(){
    return charisma;
}