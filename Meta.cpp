#include "Meta.h"
#include <iostream>
#include <algorithm>

Meta::Meta(){
    // TODO: They must pick a diety if they are paladin, cleric, monk, or druid.
    silver = 0;
    proteinShakes = 1;
    // Get the character's name
    std::cout << "Enter your character's name:\n";
    std::string charName;
    getline(std::cin, charName);
    characterName = charName;
    // Get the character's class
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
    // Picking a diety to worship
    characterDiety = "None";
    std::string charDietyInput;
    if(charClass == "Druid"){
        std::cout << "\nSelect a diety by entering the corresponding number:\n";
        std::cout << "1) Solari\n";
        std::cout << "2) Terraflora\n";
        std::cout << "3) Selunara\n";
        while(true){
            std::getline(std::cin, charDietyInput);
            if(charDietyInput == "1"){
                characterDiety = "Solari";
                break;
            }
            if(charDietyInput == "2"){
                characterDiety = "Terraflora";
                break;
            }
            if(charDietyInput == "3"){
                characterDiety = "Selunara";
                break;
            }
            std::cout << "Input not recognized. Please try again.\n";
        }
    }
    if(charClass == "Cleric" || charClass == "Monk" || charClass == "Paladin"){
        std::cout << "\nSelect a diety by entering the corresponding number:\n";
        std::cout << "1) Solari\n";
        std::cout << "2) Terraflora\n";
        std::cout << "3) Selunara\n";
        std::cout << "4) Bei\n";
        std::cout << "5) Necrotar\n";
        std::cout << "6) Leer\n";
        while(true){
            std::getline(std::cin, charDietyInput);
            if(charDietyInput == "1"){
                characterDiety = "Solari";
                break;
            }
            if(charDietyInput == "2"){
                characterDiety = "Terraflora";
                break;
            }
            if(charDietyInput == "3"){
                characterDiety = "Solari";
                break;
            }
            if(charDietyInput == "4"){
                characterDiety = "Bei";
                break;
            }
            if(charDietyInput == "5"){
                characterDiety = "Necrotar";
                break;
            }
            if(charDietyInput == "6"){
                characterDiety = "Leer";
                break;
            }
            std::cout << "Input not recognized. Please try again.\n";
        }
    }

    // Now we need to add the companion to the list of companions
    Companion player = Companion(charName, charClass, characterDiety);
    companions.push_back(player);
    // Adjust stats based on class
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
    // Make journal
    journal = Journal();
}

std::string Meta::getCharName(){
    return characterName;
}

std::string Meta::getCharDiety(){
    return characterDiety;
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
    if(companions.size() == 5){ // Too many party members now...
        std::cout << "\n#-----#-----#\n\n";
        std::cout << "Your party is full. You must ask one of your companions to travel seperately...\n";
        std::cout << "(Enter the number corresponding to the companion you'd like to release)\n";
        int currIndex = 1;
        for(auto x : companions){
            if(x.getName() != characterName){
                std::cout << currIndex << ") " << x.getName();
                currIndex++;
            }
        }
        std::string inputStr;
        while(true){ // The player enters the number for the companion they want to release
            getline(std::cin, inputStr);
            if(inputStr == "1"){
                companions.erase(companions.begin() + 1);
                break;
            }
            if(inputStr == "2"){
                companions.erase(companions.begin() + 2);
                break;
            }
            if(inputStr == "3"){
                companions.erase(companions.begin() + 3);
                break;
            }
            if(inputStr == "4"){
                companions.erase(companions.begin() + 4);
                break;
            }
            std::cout << "Input not recognized. Please try again.\n";
        }
    }
}

void Meta::removeCompanion(std::string name){
    for(int i = 0; i < (int)companions.size(); i++){
        if(companions[i].getName() == name){
            companions.erase(companions.begin() + i);
        }
    }
}

// This is for battles
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