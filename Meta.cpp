#include "Meta.h"
#include <iostream>
#include <algorithm>

Meta::Meta(){
    silver = 0;
    proteinShakes = 1;
    weaponInventory = {};
    armorInventory = {};
    // Get the character's name
    std::cout << "Enter your character's name:\n";
    std::string charName;
    while(true){
        getline(std::cin, charName);
        if(charName == "Raven" || charName == "Vivian" || charName == "Hubert" || charName == "Shrugmini" || charName == "Noam" || charName == "Iris" || charName == "Jasper"){
            std::cout << "This is the name of a character that is essential to the plot. Please pick a new name.\n";
            continue;
        }
        characterName = charName;
        break;
    }
    
    // Get the character's class
    std::cout << "\nSelect a class by entering the corresponding number:\n\n";
    std::cout << "1) Barbarian\n";
    std::cout << "-- Tough fighters who use anger to their advantage.\n\n";
    std::cout << "2) Wizard\n";
    std::cout << "-- Scholars who are well versed in the art of magic.\n\n";
    std::cout << "3) Rogue\n";
    std::cout << "-- Former criminals who use deception and stealth to their advantage.\n\n";
    std::cout << "4) Druid\n";
    std::cout << "-- Servants of the deities of nature with the power to turn into animals.\n\n";
    std::cout << "5) Hunter\n";
    std::cout << "-- Experts of survival who gather food for their community (picking this class provides a pet wolf).\n\n";
    std::cout << "6) Monk\n";
    std::cout << "-- Masters of martial arts who practice meditation in order to communicate to their deity.\n\n";
    std::cout << "7) Cleric\n";
    std::cout << "-- Priests who have been trusted by their deity to wield special powers.\n\n";
    std::cout << "8) Paladin\n";
    std::cout << "-- Loyal knights who defend those worshipping the same deity.\n\n";
    std::cout << "9) Artisan\n";
    std::cout << "-- Skilled crafters who can improve weapons and armor.\n\n";
    std::cout << "10) Explorer\n";
    std::cout << "-- Smart and charismatic individuals who are weak in combat but strong elsewhere.\n";
    std::cout << "Warning: Picking explorer will result in a uniquely challenging experience.\n";
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
            charClass = "Hunter";
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
        if(charClassInput == "9"){
            charClass = "Artisan";
            break;
        }
        if(charClassInput == "10"){
            charClass = "Explorer";
            break;
        }
        std::cout << "Input not recognized. Please try again.\n";
    }
    // Picking a deity to worship
    characterDeity = "None";
    std::string charDeityInput;
    if(charClass == "Druid"){
        std::cout << "\nSelect a deity by entering the corresponding number:\n";
        std::cout << "1) Solari\n";
        std::cout << "2) Terraflora\n";
        std::cout << "3) Selunara\n";
        while(true){
            std::getline(std::cin, charDeityInput);
            if(charDeityInput == "1"){
                characterDeity = "Solari";
                break;
            }
            if(charDeityInput == "2"){
                characterDeity = "Terraflora";
                break;
            }
            if(charDeityInput == "3"){
                characterDeity = "Selunara";
                break;
            }
            std::cout << "Input not recognized. Please try again.\n";
        }
    }
    if(charClass == "Cleric" || charClass == "Monk" || charClass == "Paladin"){
        std::cout << "\nSelect a deity by entering the corresponding number:\n";
        std::cout << "1) Solari\n";
        std::cout << "2) Terraflora\n";
        std::cout << "3) Selunara\n";
        std::cout << "4) Bei\n";
        std::cout << "5) Necrotar\n";
        std::cout << "6) Leer\n";
        while(true){
            std::getline(std::cin, charDeityInput);
            if(charDeityInput == "1"){
                characterDeity = "Solari";
                break;
            }
            if(charDeityInput == "2"){
                characterDeity = "Terraflora";
                break;
            }
            if(charDeityInput == "3"){
                characterDeity = "Selunara";
                break;
            }
            if(charDeityInput == "4"){
                characterDeity = "Bei";
                break;
            }
            if(charDeityInput == "5"){
                characterDeity = "Necrotar";
                break;
            }
            if(charDeityInput == "6"){
                characterDeity = "Leer";
                break;
            }
            std::cout << "Input not recognized. Please try again.\n";
        }
    }
    if(charClass == "Hunter"){
        std::cout << "\nName your pet wolf:\n";
        std::string wolfName;
        while(true){
            getline(std::cin, wolfName);
            if(wolfName == "Raven" || wolfName == "Vivian" || wolfName == "Hubert" || wolfName == "Shrugmini" || wolfName == "Noam" || wolfName == "Iris" || wolfName == "Jasper"){
                std::cout << "This is the name of a character that is essential to the plot. Please pick a new name.\n";
                continue;
            }
            if(wolfName == characterName){
                std::cout << "You should name your pet differently than yourself. Please pick a new name.\n";
                continue;
            }
            break;
        }
        Companion wolf = Companion(wolfName, "Wolf", "None");
        wolf.levelUp();
        companions.push_back(wolf);
    }

    // Now we need to add the companion to the list of companions
    Companion player = Companion(charName, charClass, characterDeity);
    player.levelUp();
    companions.push_back(player);
    // Adjust stats based on class
    perception = 0;
    if(charClass == "Wizard") perception++;
    if(charClass == "Rogue") perception+=2;
    if(charClass == "Druid") perception++;
    if(charClass == "Hunter") perception++;
    if(charClass == "Explorer") perception+=100;
    charisma = 0;
    if(charClass == "Barbarian") charisma--;
    if(charClass == "Wizard") charisma++;
    if(charClass == "Rogue") charisma+=2;
    if(charClass == "Explorer") charisma+=100;
    // Make journal
    journal = Journal();
}

std::string Meta::getCharName(){
    return characterName;
}

std::string Meta::getCharDeity(){
    return characterDeity;
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
    // We check to see if the player is a hunter since their wolf does not count as a companion
    int isNotHunter = 1;
    for(auto x : companions){
        if(x.getType() == "Hunter"){
            isNotHunter = 0;
        }
    }
    if(companions.size() == 6 - isNotHunter){ // Too many party members now...
        std::cout << "\n#-----#-----#\n\n";
        std::cout << "Your party is full. You must ask one of your companions to travel seperately...\n";
        std::cout << "(Enter the number corresponding to the companion you'd like to release)\n";
        int currIndex = 1;
        std::string companionNames[4];
        for(auto x : companions){
            if(x.getName() != characterName){
                companionNames[currIndex-1] = x.getName();
                std::cout << currIndex << ") " << x.getName();
                currIndex++;
            }
        }
        std::string inputStr;
        bool loopThing = true;
        while(loopThing){ // The player enters the number for the companion they want to release
            getline(std::cin, inputStr);
            if(inputStr == "1"){
                for(int i = 0; i < (int)companions.size(); i++){ // Go through the companions and remove the one that matches the name
                    if(companions[i].getName() == companionNames[0]){
                        companionNames[0] = companions[i].getName(); // We will later check the name to remove the quest
                        companions.erase(companions.begin() + i);
                        loopThing = false;
                        break;
                    }
                }
            }
            if(inputStr == "2"){
                for(int i = 0; i < (int)companions.size(); i++){
                    if(companions[i].getName() == companionNames[1]){
                        companionNames[0] = companions[i].getName(); // We will later check the name to remove the quest
                        companions.erase(companions.begin() + i);
                        loopThing = false;
                        break;
                    }
                }
            }
            if(inputStr == "3"){
                for(int i = 0; i < (int)companions.size(); i++){
                    if(companions[i].getName() == companionNames[2]){
                        companionNames[0] = companions[i].getName(); // We will later check the name to remove the quest
                        companions.erase(companions.begin() + i);
                        loopThing = false;
                        break;
                    }
                }
            }
            if(inputStr == "4"){
                for(int i = 0; i < (int)companions.size(); i++){
                    if(companions[i].getName() == companionNames[3]){
                        companionNames[0] = companions[i].getName(); // We will later check the name to remove the quest
                        companions.erase(companions.begin() + i);
                        loopThing = false;
                        break;
                    }
                }
            }
            if(!loopThing){ // Companion was successfully selected
                if(companionNames[0] == "Raven"){
                    journal.advanceQuest(3, -1, "We decided not to travel with Raven.", true);
                }
                if(companionNames[0] == "Vivian"){
                    journal.advanceQuest(4, -1, "We decided not to travel with Vivian.", true);
                }
                if(companionNames[0] == "Shrugmini"){
                    journal.advanceQuest(5, -1, "We decided not to travel with Shrugmini.", true);
                }
                if(companionNames[0] == "Iris"){
                    journal.advanceQuest(6, -1, "We decided not to travel with Iris.", true);
                }
                if(companionNames[0] == "Hubert"){
                    journal.advanceQuest(7, -1, "We decided not to travel with Hubert.", true);
                }
                if(companionNames[0] == "Noam"){
                    journal.advanceQuest(8, -1, "We decided not to travel with Noam.", true);
                }
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

int Meta::getPerception(){
    return perception;
}

int Meta::getCharisma(){
    return charisma;
}

void Meta::addArmor(Armor armor){
    armorInventory.push_back(armor);
    std::cout << "\n\033[0;36mA new piece of armor was added to your inventory.\033[0;0m\n";
}

void Meta::addWeapon(Weapon weapon){
    weaponInventory.push_back(weapon);
    std::cout << "\n\033[0;36mA new weapon was added to your inventory.\033[0;0m\n";
}