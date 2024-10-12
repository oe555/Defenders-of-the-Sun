#include "Enemy.h"
#include "Quest.h"
#include "Journal.h"
#include "Weapon.h"
#include "Armor.h"
#include "Companion.h"
#include "Meta.h"
#include "Location.h"
#include "Interaction.h"
#include "Region.h"
#include "Dialogue.h"
#include "MapGen.h"
#include "Rest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const std::string resettext("\033[0;0m");
const std::string boldtext("\033[0;1m");
const std::string redtext("\033[0;31m");
const std::string redboldtext("\033[1;31m");
const std::string greentext("\033[0;32m");
const std::string greenboldtext("\033[1;32m");
const std::string bluetext("\033[0;36m");
const std::string blueboldtext("\033[1;36m");
const std::string purpleboldtext("\033[1;35m");
const std::string greyittext("\033[3;37m");

bool checkForDigit(std::string str){ // Checks to see if the user entered some number
    for(int i = 0; i < (int)str.size(); i++){
        if(str[i] >= '0' && str[i] <= '9') return true;
    }
    return false;
}

std::string pad(std::string str){
    const int maxLineLength = 150; // This is the max number of lines that will show on any line in the terminal.
    int currLineLength = 0;
    int lastSpace = 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == ' '){
            lastSpace = i;
        }
        if(str[i] == '\n'){
            currLineLength = 0;
        }
        if(currLineLength >= maxLineLength){
            str[lastSpace] = '\n';
            currLineLength = i - lastSpace;
        }
        else{
            currLineLength++;
        }
    }
    return str;
}

void separatorBar(){
    std::cout << "\n#-----#-----#\n\n";
}

// Calling this functions prompts the player to pick an enemy from the given vector
int selectEnemy(std::vector<Enemy> &enemies){
    for(int i = 0; i < enemies.size(); i++){
        std::cout << i+1 << ") " << enemies[i].getName() << "\n";
    }
    std::string inpString = "";
    int inpInt = 0;
    while(true){
        getline(std::cin, inpString);
        if(!checkForDigit(inpString)){
            std::cout << "Input not recognized. Please try again.\n";
            continue;
        }
        int inpInt = stoi(inpString);
        inpInt--;
        if(inpInt < 0 || inpInt >= (int)enemies.size()){
            std::cout << "Input not recognized. Please try again.\n";
            continue;
        }
        std::cout << purpleboldtext << "-----\n" << resettext;
        return inpInt;
    }
    return inpInt;
}

// Calling this function prompts the player to pick a companion from the given meta object
int selectAlly(Meta meta){
    for(int i = 0; i < meta.companions.size(); i++){
        std::cout << i+1 << ") " << meta.companions[i].getName() << " [" << meta.companions[i].getHealth() << "/" << meta.companions[i].getMaxHealth() << "]\n";
    }
    std::string inpString = "";
    int inpInt = 0;
    while(true){
        getline(std::cin, inpString);
        if(!checkForDigit(inpString)){
            std::cout << "Input not recognized. Please try again.\n";
            continue;
        }
        int inpInt = stoi(inpString);
        inpInt--;
        if(inpInt < 0 || inpInt >= (int)meta.companions.size()){
            std::cout << "Input not recognized. Please try again.\n";
            continue;
        }
        std::cout << purpleboldtext << "-----\n" << resettext;
        return inpInt;
    }
    return inpInt;
}

// Return true if they win on their turn
bool enemiesTurn(std::vector<Enemy> &enemies, Meta &meta){
    //separatorBar();
    bool checkCompanions = false;
    int statusDamage = 0;
    std::string trashLine;
    for(int currEnemy = 0; currEnemy < (int)enemies.size(); currEnemy++){
        // RESOLVE STATUS EFFECTS
        if(enemies[currEnemy].hasStatusEffect("Poison")){
            statusDamage = rand() % 4 + 1;
            std::cout << enemies[currEnemy].getName() << " took " << statusDamage << " poison damage.\n";
            enemies[currEnemy].takeDamage(statusDamage, 100); // Always hit
            enemies[currEnemy].setHealth(std::max(enemies[currEnemy].getHealth(), 1)); // Status damage can't kill
            std::cout << enemies[currEnemy].getName() << " now has " << enemies[currEnemy].getHealth() << " health.\n";
        }

        int currTarget = 0;
        if(enemies[currEnemy].isIntelligent()){ // Intellegent enemies attack the lowest health companion
            for(int i = 1; i < (int)meta.companions.size(); i++){
                // Find the least health companion that is not down or hiding
                if((meta.companions[i].getHealth() < meta.companions[currTarget].getHealth() && meta.companions[i].getHealth() > 0 && !meta.companions[i].hiding) || meta.companions[currTarget].getHealth() <= 0) currTarget = i;
            }
        }
        else{
            // Attack a random companion that is not down
            //srand(time(NULL));
            currTarget = rand() % meta.companions.size();
            while(meta.companions[currTarget].getHealth() <= 0){
                currTarget = rand() % meta.companions.size();
            }
        }
        //separatorBar();
        std::cout << boldtext << enemies[currEnemy].getName() << " attempted to attack " << meta.companions[currTarget].getName() << ".\n" << resettext;
        if(meta.companions[currTarget].hiding){ // Enemies cannot attack hidden targets
            std::cout << "The enemy could not find their target...\n";
        }
        else if(meta.companions[currTarget].takeDamage(enemies[currEnemy].dealDamage())){
            std::cout << "The enemy's attack was successful.\n";
            std::cout << meta.companions[currTarget].getName() << "'s health has been reduced to " << meta.companions[currTarget].getHealth() << "/" << meta.companions[currTarget].getMaxHealth() << ".\n";
        }
        else{
            std::cout << "The enemy missed their attack.\n";
        }
        if(meta.companions[currTarget].getHealth() <= 0){
            std::cout << redtext << meta.companions[currTarget].getName() << " is now severely weakened!\n" << resettext;
        }
        std::cout << "<Press Enter to continue>";
        getline(std::cin, trashLine);
        separatorBar();
        checkCompanions = true;
        for(int i = 0; i < (int)meta.companions.size(); i++){
            if(meta.companions[i].getHealth() > 0) checkCompanions = false; // We don't want to return if there's a companion that isn't down
        }
        if(checkCompanions) return true; // Return true if all companions are down
    }
    for(int i = 0; i < (int)meta.companions.size(); i++){ // This is a final check we do to make sure there is a companion that isn't down
        if(meta.companions[i].getHealth() > 0) return false;
    }
    return true;
}

// Return true if they win on their turn
bool playerTurn(std::vector<Enemy> &enemies, Meta &meta){
    //separatorBar();
    // TODO: Maybe output some information about the party here
    std::cout << "Your party prepares to attack. You currently have " << meta.getProteinShakes() << " protein shakes.\n";
    for(int i = 0; i < (int)meta.companions.size(); i++){ // This loop iterates over all companions
        if(meta.companions[i].getHealth() <= 0){ // We inform the player and continue when the companion is at 0 hp
            std::cout << meta.companions[i].getName() << " is very weak.\n";
            separatorBar();
            continue;
        }
        else{ // Otherwise we provide their HP and list status effects
            std::cout << meta.companions[i].getName() << "'s current health: " << meta.companions[i].getHealth() << "/" << meta.companions[i].getMaxHealth() << ".\n";
            if(meta.companions[i].hiding){
                std::cout << meta.companions[i].getName() << " is hiding. Attacks will reveal but deal " << meta.companions[i].getLevel() * 2 << " more damage.\n";
            }
            if(meta.companions[i].raging){
                std::cout << meta.companions[i].getName() << " is raging. Attacks will deal " << meta.companions[i].getLevel() + 4 << " more damage.\n";
            }
            if(meta.companions[i].inspired){
                std::cout << meta.companions[i].getName() << " is inspired. Attacks will deal " << meta.companions[i].getLevel() + 1 << " more damage.\n";
            }
            if(meta.companions[i].healUsed){
                std::cout << meta.companions[i].getName() << " is low on adrenaline. Healing will only restore 1 HP.\n";
            }
            std::cout << "\n";
        }
        // This is where the player will pick their action
        std::cout << blueboldtext << meta.companions[i].getName() << "'s action:\n" << resettext;
        std::string actionChoice;
        for(int j = 0; j < (int)meta.companions[i].getActions().size(); j++){
            std::cout << j+1 << ") " << meta.companions[i].getActions()[j] << "\n";
        }
        while(true){
            getline(std::cin, actionChoice);
            if(!checkForDigit(actionChoice)){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            int actionChoiceInt = stoi(actionChoice);
            actionChoiceInt--;
            if(actionChoiceInt < 0 || actionChoiceInt >= (int)meta.companions[i].getActions().size()){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            std::cout << purpleboldtext << "-----\n" << resettext;
            // actionChoice now stores the name of the action instead of the number from the input
            actionChoice = meta.companions[i].getActions()[actionChoiceInt];
            break;
        }
        /*
            If statements for every possible action because we love spaghetti
        */
        if(actionChoice == "Attack"){
            int targetEnemy;
            for(int j = 0; j < meta.companions[i].getAttackCount(); j++){ // Accounts for extra attacks
                if(enemies.empty()) break; // Don't keep prompting if all the enemies died
                std::cout << "Select the enemy you'd like to attack.\n";
                //std::cout << "DEBUG\n";
                targetEnemy = selectEnemy(enemies);
                //std::cout << "Selected enemy: " << targetEnemy << "\n";
                std::cout << boldtext << meta.companions[i].getName() << " attempts to attack " << enemies[targetEnemy].getName() << "\n" << resettext;
                if(enemies[targetEnemy].takeDamage(meta.companions[i].dealDamage(), meta.companions[i].getWeapon().getPrecisionBonus() + (meta.companions[i].hiding ? 100 : 0))){
                    std::cout << greentext << "Your attack was successful.\n" << resettext;
                    std::cout << enemies[targetEnemy].getName() << "'s health has been reduced to " << enemies[targetEnemy].getHealth() << ".\n";
                }
                else{
                    std::cout << redtext << "You missed your attack.\n" << resettext;
                }
                if(enemies[targetEnemy].getHealth() <= 0){ // Check to see if they were killed
                    std::cout << greentext << enemies[targetEnemy].getName() << " was defeated!\n" << resettext;
                    enemies.erase(enemies.begin() + targetEnemy);
                }
            }
        }
        if(actionChoice == "Drink Protein"){
            if(meta.drinkProteinShake()){
                meta.companions[i].setHealth(std::min(meta.companions[i].getHealth() + 10, meta.companions[i].getMaxHealth()));
                std::cout << "You consume a protein shake and gain 10 health. You now have " << meta.companions[i].getHealth() << "/" << meta.companions[i].getMaxHealth() << " health points.\n";
            }
            else{
                std::cout << "You reach into your bag and realize that you don't have any protein shakes left!\n";
            }
        }
        if(actionChoice == "Rage"){
            std::cout << "You are now raging.\n";
            meta.companions[i].raging = true;
        }
        if(actionChoice == "Zap"){
            std::cout << "Select the enemy you'd like to zap.\n";
            int targetEnemy = selectEnemy(enemies);
            std::cout << boldtext << meta.companions[i].getName() << " zaps " << enemies[targetEnemy].getName() << "\n" << resettext;
            enemies[targetEnemy].takeDamage(5, 100); // Precision level 100 makes it always hit
            std::cout << enemies[targetEnemy].getName() << "'s health has been reduced to " << enemies[targetEnemy].getHealth() << ".\n";
            if(enemies[targetEnemy].getHealth() <= 0){ // Check to see if they were killed
                std::cout << greentext << enemies[targetEnemy].getName() << " was defeated!\n" << resettext;
                enemies.erase(enemies.begin() + targetEnemy);
            }
        }
        if(actionChoice == "Hide"){
            std::cout << "You are now hiding.\n";
            meta.companions[i].hiding = true;
        }
        if(actionChoice == "Snake Bite"){
            std::cout << "Select the enemy you'd like to bite.\n";
            int targetEnemy = selectEnemy(enemies);
            std::cout << boldtext << meta.companions[i].getName() << " bites " << enemies[targetEnemy].getName() << "\n" << resettext;
            enemies[targetEnemy].addStatusEffect("Poison");
            std::cout << enemies[targetEnemy].getName() << " has been poisoned.\n";
        }
        if(actionChoice == "Wolf Bite"){
            std::cout << "Select the enemy you'd like to bite.\n";
            int targetEnemy = selectEnemy(enemies);
            std::cout << boldtext << meta.companions[i].getName() << " bites " << enemies[targetEnemy].getName() << "\n" << resettext;
            if(enemies[targetEnemy].getHealth() <= 15){ // Wolf bite only hits when HP is less than 15
                enemies[targetEnemy].takeDamage(5 + meta.companions[i].getLevel(), 100); // Precision level 100 makes it always hit
                std::cout << enemies[targetEnemy].getName() << "'s health has been reduced to " << enemies[targetEnemy].getHealth() << ".\n";
                if(enemies[targetEnemy].getHealth() <= 0){ // Check to see if they were killed
                    std::cout << greentext << enemies[targetEnemy].getName() << " was defeated!\n" << resettext;
                    enemies.erase(enemies.begin() + targetEnemy);
                }
            }
            else{
                std::cout << "The target enemy is not weak enough to be affected by wolf bite.\n";
            }
        }
        if(actionChoice == "Heal"){
            std::cout << "Choose an Ally to heal.\n";
            int targetAlly = selectAlly(meta);
            if(!meta.companions[i].healUsed){ // Heal has not been used, thus it will restore 5 + level
                meta.companions[targetAlly].setHealth(std::min(meta.companions[targetAlly].getHealth() + 5 + meta.companions[i].getLevel(), meta.companions[targetAlly].getMaxHealth()));
            }
            else{ // Heals after the first only heal 1
                meta.companions[targetAlly].setHealth(std::min(meta.companions[targetAlly].getHealth() + 1, meta.companions[targetAlly].getMaxHealth()));
            }
            std::cout << meta.companions[targetAlly].getName() << " was healed. They now have " << meta.companions[targetAlly].getHealth() << "/" << meta.companions[targetAlly].getMaxHealth() << " health points.\n";
            meta.companions[i].healUsed = true; // We used heal
        }
        if(actionChoice == "Agonize"){
            int targetEnemy;
            for(int j = 0; j < meta.companions[i].getAgonizeCount(); j++){ // Accounts for extra attacks
                std::cout << "Select the enemy you'd like to agonize.\n";
                //std::cout << "DEBUG\n";
                targetEnemy = selectEnemy(enemies);
                //std::cout << "Selected enemy: " << targetEnemy << "\n";
                std::cout << boldtext << meta.companions[i].getName() << " attempts to agonize " << enemies[targetEnemy].getName() << "\n" << resettext;
                if(enemies[targetEnemy].takeDamage(3 * meta.companions[i].getLevel(), 0)){
                    std::cout << greentext << "The spell successfully hit the enemy.\n" << resettext;
                    std::cout << enemies[targetEnemy].getName() << "'s health has been reduced to " << enemies[targetEnemy].getHealth() << ".\n";
                }
                else{
                    std::cout << redtext << "You missed your spell.\n" << resettext;
                }
                if(enemies[targetEnemy].getHealth() <= 0){ // Check to see if they were killed
                    std::cout << greentext << enemies[targetEnemy].getName() << " was defeated!\n" << resettext;
                    enemies.erase(enemies.begin() + targetEnemy);
                }
            }
        }
        if(actionChoice == "Inspire"){
            std::cout << "Choose an Ally to inspire.\n";
            int targetAlly = selectAlly(meta);
            meta.companions[targetAlly].inspired = true;
            std::cout << meta.companions[targetAlly].getName() << " is now inspired.\n";
        }
        separatorBar();
        if(enemies.empty()){
            return true;
        }
    }
    return false;
}

// Return true if the player loses. DO NOT CALL THIS FUNCTION DIRECTLY.... ALWAYS USE runEncounter()
bool encounter(std::vector<Enemy> &enemies, Meta &meta, bool ambush){
    separatorBar();
    std::cout << "--- Combat Initiated ---\n";
    if(ambush) std::cout << "Your party is surprised! Enemies act first.\n";
    separatorBar();
    std::random_shuffle(enemies.begin(), enemies.end());
    meta.shuffleCompanions();
    if(ambush) if(enemiesTurn(enemies, meta)) return true;
    while(true){
        if(playerTurn(enemies, meta)) return false;
        if(enemiesTurn(enemies, meta)) return true;
    }
}

/*
This function starts an encounter with the provided enemies. Returns true if the enemies win.
*/
bool runEncounter(std::vector<Enemy> &enemies, Meta &meta, bool ambush){
    if(encounter(enemies, meta, ambush)){
        separatorBar();
        std::cout << redboldtext << "Your party has been defeated...\n" << resettext;
        separatorBar();
        return true;
    }
    else{
        separatorBar();
        std::cout << greenboldtext << "Your party successfully survived the encounter!\n" << resettext;
        separatorBar();
        // Reset status effects
        for(int i = 0; i < meta.companions.size(); i++){
            meta.companions[i].resetStatusEffects();
        }
        return false;
    }
}

int main(){ 
    srand(time(NULL));
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << greenboldtext << "Defenders of the Sun\n" << resettext;
    std::cout << bluetext << "When navigating menus, enter the number corresponding to your choice and press enter. To exit the game, press control + C.\n" << resettext;
    std::cout << "Disclaimer: This story was written for a mature audience. Topics such as sex, religion, and death are explored in detail.\n";
    std::string mainMenuInput;
    while(true){
        std::cout << "1) Start a new adventure\n";
        std::cout << "2) Read about the world in which this adventure takes place (recommended)\n"; 
        getline(std::cin, mainMenuInput);
        if(mainMenuInput == "1"){
            break;
        }
        else if(mainMenuInput == "2"){
            std::cout << pad("Defenders of the Sun takes place in a world consisting of humans, elves, dwarves, and other various common mythological creatures.\n\nIn this universe, gods (referred to as deities) are real. There are many deities that govern the universe, and they are commonly worshipped among mortals. The deities that are important to this story are introduced here:\n\n");
            std::cout << "- Solari: God of the sun (lawful good)\n";
            std::cout << "- Selunara: Goddess of the moon (chaotic good)\n";
            std::cout << "- Leer: Goddess of darkness and night (chaotic evil)\n";
            std::cout << pad("The deities listed above are siblings. Followers of Leer are typically enemies with followers of the other two as they believe light is a distraction from self awareness and reflection.\n");
            std::cout << "- Terraflora: Goddess of nature (neutral good)\n";
            std::cout << "- Bei: Goddess of War (lawful evil)\n";
            std::cout << "- Necrotar: God of death (neutral evil)\n\n";
            std::cout << pad("There exists many clerics, paladins, and monks with powers that are sponsored by their deity. Druids are only sponsored by deities that govern nature in some way.\n\n");
            std::cout << pad("Magic exists in the world, but only certain people can use it. Those who use magic are either sponsored by a deity or other very powerful figure or have spent lots of time studying (wizards are scholars and don't have patrons, but witches/warlocks do).\n\n");
            std::cout << pad("The underworld exists, but nobody knows much about it or how to get there. Devils live in the underworld and seek to control the surface, but the deities keep them trapped in the underworld to maintain balance.\n\n");
            std::cout << "#-----#-----#\n\n";
            std::cout << "Select a new option from the menu:\n";
        }
        else{
            std::cout << "Input not recognized. Please try again.\n";
        }
    }

    /*
        START ADVENTURE!!!!!!!!!!!!!!!
    */
    Meta meta = Meta();
    Region regA = GenRegionA(meta); // Generate the first region
    int currLocationIndex = 0; // Current location is A0
    Location *currLocation;
    int interactionRes;
    int currOptionIndex = 0;
    std::string inpStr;
    int inp;
    while(true){
        regA.markAsVisited(currLocationIndex);
        currLocation = &(regA.locations[currLocationIndex]);
        std::cout << "\nCurrent Location: " << currLocation->getName() << "\n";
        if(currLocation->getHasPrimaryInteraction()){ // Run the primary interaction if we haven't already
            interactionRes = currLocation->getPrimaryInteraction().runInteraction(meta); // This will also remove the primary interaction
            if(interactionRes == 1){ // The interaction results in an encounter
                std::vector<Enemy> temp = currLocation->getEnemies();
                if(runEncounter(temp, meta, false)){ // TODO: AMBUSHES (also figure out whether we need temp)
                    return 0;
                } 
                if(currLocation->getHasPostEncounterInteraction()){
                    currLocation->getPostEncounterInteraction().runInteraction(meta); // This will never result in an encounter
                }
            }
        }
        // Give player options for what to do
        currOptionIndex = 1;
        std::cout << "\n";
        for(int i = 0; i < currLocation->getNumOptionalInteractions(); i++){
            std::cout << currOptionIndex << ") " << currLocation->getOptionalInteraction(i).first << "\n";
            currOptionIndex++;
        }
        std::cout << currOptionIndex << ") Move to a nearby location\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") View active quests\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") View completed quests\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") View party information\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") Drink protein (restores 10 health)\n";
        currOptionIndex++;
        while(true){ // Get the input from the user
            getline(std::cin, inpStr);
            if(!checkForDigit(inpStr)){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            inp = stoi(inpStr); // TODO: Runtime error
            if(inp < 1 || inp >= currOptionIndex){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            std::cout << purpleboldtext << "-----\n" << resettext;
            break;
        } // inp now stores their choice
        if(inp <= currLocation->getNumOptionalInteractions()){
            Interaction optionalInteraction = currLocation->getOptionalInteraction(inp - 1).second;
            interactionRes = optionalInteraction.runInteraction(meta);
            if(interactionRes != 0){
                //std::cout << "\n[DEV] REMOVING OPTIONAL INTERACTION\n\n";
                currLocation->removeOptionalInteraction(inp - 1);
                //std::cout << "\n[DEV] OPTIONAL INTERACTION REMOVED\n\n";
            }
            if(interactionRes == 1){ // The interaction results in an encounter
                std::vector<Enemy> temp = currLocation->getEnemies();
                if(runEncounter(temp, meta, false)){ // TODO: AMBUSHES (also figure out whether we need temp)
                    return 0;
                } 
                if(currLocation->getHasPostEncounterInteraction()){
                    currLocation->getPostEncounterInteraction().runInteraction(meta); // This will never result in an encounter
                }
            }
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 1){ // Move to a nearby location
            currOptionIndex = 1; // Utilize these variables to prompt the choice of where to go
            std::string optionColor = resettext;
            for(int i = 0; i < regA.getAdj(currLocationIndex).size(); i++){ // Outputs the names of the adjacent locations
                if(regA.hasBeenVisited(regA.getAdj(currLocationIndex)[i])) optionColor = greyittext;
                else optionColor = resettext;
                std::cout << currOptionIndex << ") " << optionColor << regA.locations[regA.getAdj(currLocationIndex)[i]].getName() << resettext << "\n";
                currOptionIndex++;
            }
            while(true){
                getline(std::cin, inpStr);
                if(!checkForDigit(inpStr)){
                    std::cout << "Input not recognized. Please try again.\n";
                    continue;
                }
                inp = stoi(inpStr);
                if(inp < 1 || inp >= currOptionIndex){
                    std::cout << "Input not recognized. Please try again.\n";
                    continue;
                }
                std::cout << purpleboldtext << "-----\n" << resettext;
                break;
            }
            // Update currLocationIndex
            currLocationIndex = regA.getAdj(currLocationIndex)[inp-1];
            // If we end up in the location of the campsite, we should move on to act 2 (region B)
            if(currLocationIndex == 22) break;
            continue;
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 2){ // View active quests
            meta.journal.listQuests(false);
            continue;
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 3){ // View completed quests
            meta.journal.listQuests(true);
            continue;
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 4){ // View party information
            std::string trashLine;
            std::cout << "\n#-----#-----#\n\n";
            std::cout << "Silver: " << meta.getSilver() << "\n";
            std::cout << "Protein Shakes: " << meta.getProteinShakes() << "\n\n";
            std::cout << "Your perception bonus: " << meta.getPerception() << "\n";
            std::cout << "Your charisma bonus: " << meta.getCharisma() << "\n";
            for(auto x : meta.companions){
                std::cout << "\n#-----#-----#\n\n";
                x.getDetails();
                std::cout << "<Press Enter to continue>";
                getline(std::cin, trashLine);
            }
            std::cout << "\n#-----#-----#\n\n";
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 5){ // Drink protein
            if(meta.drinkProteinShake()){
                int theChoice = selectAlly(meta);
                meta.companions[theChoice].setHealth(std::min(meta.companions[theChoice].getHealth() + 10, meta.companions[theChoice].getMaxHealth()));
                std::cout << meta.companions[theChoice].getName() << " consumed a protein shake and gained 10 health. They now have " << meta.companions[theChoice].getHealth() << "/" << meta.companions[theChoice].getMaxHealth() << " health points.\n";
            }
            else{
                std::cout << "You reach into your bag and realize that you don't have any protein shakes left!\n";
            }
        }
    }
    regA.endingRest.executeRest(meta);
    return 0;
}
