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
        // TODO: Potential runtime error
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
        std::cout << i+1 << ") " << meta.companions[i].getName() << "\n";
    }
    std::string inpString = "";
    int inpInt = 0;
    while(true){
        getline(std::cin, inpString);
        // TODO: Potential runtime error
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
        std::cout << boldtext << "Enemy " << enemies[currEnemy].getName() << " attempted to attack " << meta.companions[currTarget].getName() << ".\n" << resettext;
        if(meta.companions[currTarget].hiding){ // Enemies cannot attack hidden targets
            std::cout << "The enemy could not find their target...\n";
        }
        else if(meta.companions[currTarget].takeDamage(enemies[currEnemy].dealDamage())){
            std::cout << "The enemy's attack was successful.\n";
            std::cout << meta.companions[currTarget].getName() << "'s health has been reduced to " << meta.companions[currTarget].getHealth() << ".\n";
        }
        else{
            std::cout << "The enemy missed their attack.\n";
        }
        if(meta.companions[currTarget].getHealth() <= 0){
            std::cout << redtext << meta.companions[currTarget].getName() << " was knocked unconscious!\n" << resettext;
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
        if(meta.companions[i].getHealth() <= 0){ // We inform the player and continue when the companion is unconscious
            std::cout << meta.companions[i].getName() << " is unconscious.\n";
            separatorBar();
            continue;
        }
        else{ // Otherwise we provide their HP and list status effects
            std::cout << meta.companions[i].getName() << "'s current health: " << meta.companions[i].getHealth() << ".\n";
            if(meta.companions[i].hiding){
                std::cout << meta.companions[i].getName() << " is hiding.\n";
            }
            if(meta.companions[i].raging){
                std::cout << meta.companions[i].getName() << " is raging.\n";
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
            // TODO: Potential runtime error
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
            std::cout << "Select the enemy you'd like to attack.\n";
            int targetEnemy = selectEnemy(enemies);
            std::cout << boldtext << meta.companions[i].getName() << " attempts to attack " << enemies[targetEnemy].getName() << "\n" << resettext;
            if(enemies[targetEnemy].takeDamage(meta.companions[i].dealDamage(), meta.companions[i].getWeapon().getPrecisionBonus())){
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
        if(actionChoice == "Drink Protein"){
            if(meta.drinkProteinShake()){
                meta.companions[i].setHealth(meta.companions[i].getHealth() + 10);
                std::cout << "You consume a protein shake and gain 10 health. You now have " << meta.companions[i].getHealth() << " health points.\n";
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
            enemies[targetEnemy].takeDamage(2*meta.companions[i].getLevel(), 100); // Precision level 100 makes it always hit
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
        if(actionChoice == "Heal"){
            std::cout << "Choose an Ally to heal.\n";
            int targetAlly = selectAlly(meta);
            meta.companions[targetAlly].setHealth(meta.companions[targetAlly].getHealth() + 5 + meta.companions[i].getLevel());
            std::cout << meta.companions[targetAlly].getName() << " was healed. They now have " << meta.companions[targetAlly].getHealth() << " health points.\n";
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

int main(){ // Main currently has a bunch of tester code
    //companionTester();
    srand(time(NULL));
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << greenboldtext << "Defenders of the Sun\n" << resettext;
    std::cout << bluetext << "When navigating menus, enter the number corresponding to your choice and press enter. To exit the game, press control + C.\n" << resettext;
    std::string mainMenuInput;
    while(true){
        std::cout << "1) Start a new adventure\n";
        std::cout << "2) Read about the world in which this adventure takes place (recommended)\n"; 
        getline(std::cin, mainMenuInput);
        if(mainMenuInput == "1"){
            break;
        }
        else if(mainMenuInput == "2"){
            std::cout << pad("Defenders of the Sun takes place in a world consisting of humans, elves, dwarves, and other various common mythological creatures.\n\nIn this universe, gods (referred to as deities) are real. There are many deities that govern the universe (somewhere between 50 and 60), and they are commonly worshipped among mortals. The deities that are important to this story are introduced here:\n\n");
            std::cout << "- Solari: God of the sun (lawful good)\n";
            std::cout << "- Selunara: Goddess of the moon (chaotic good)\n";
            std::cout << "- Leer: Goddess of darkness and night (chaotic evil)\n";
            std::cout << pad("The deities listed above are siblings. Followers of Leer are typically enemies with followers of the other two as they believe light is a distraction from self awareness and reflection.\n");
            std::cout << "- Terraflora: Goddess of nature (neutral good)\n";
            std::cout << "- Bei: Goddess of War (lawful evil)\n";
            std::cout << "- Necrotar: God of death (neutral evil)\n\n";
            std::cout << pad("There exists many clerics, paladins, and monks with powers that are sponsored by their deity. Druids are only sponsored by deities that govern nature in some way (most druids serve Terraflora).\n\n");
            std::cout << pad("Magic exists in the world, but only certain people can use it. Those who use magic are either sponsored by a deity or other very powerful figure or have spent lots of time studying (wizards and necromancers are scholars and don't have patrons).\n\n");
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
        currLocation = &(regA.locations[currLocationIndex]);
        std::cout << "\nCurrent Location: " << currLocation->getName() << "\n";
        if(currLocation->getHasPrimaryInteraction()){ // Run the primary interaction if we haven't already
            interactionRes = currLocation->getPrimaryInteraction().runInteraction(meta);
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
            std::cout << currOptionIndex << ") " << currLocation->getOptionalInteraction(i).first;
            currOptionIndex++;
        }
        std::cout << currOptionIndex << ") Move to a nearby location\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") View active quests\n";
        currOptionIndex++;
        std::cout << currOptionIndex << ") View completed quests\n";
        currOptionIndex++;
        while(true){ // Get the input from the user
            getline(std::cin, inpStr);
            inp = stoi(inpStr); // TODO: Runtime error
            if(inp < 1 || inp >= currOptionIndex){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            std::cout << purpleboldtext << "-----\n" << resettext;
            break;
        } // inp now stores their choice
        if(inp <= currLocation->getNumOptionalInteractions()){
            // TODO: Optional interactions
        }
        else if(inp == currLocation->getNumOptionalInteractions() + 1){ // Move to a nearby location
            currOptionIndex = 1; // Utilize these variables to prompt the choice of where to go
            for(int i = 0; i < regA.getAdj(currLocationIndex).size(); i++){ // Outputs the names of the adjacent locations
                std::cout << currOptionIndex << ") " << regA.locations[regA.getAdj(currLocationIndex)[i]].getName() << "\n";
                currOptionIndex++;
            }
            while(true){
                getline(std::cin, inpStr);
                inp = stoi(inpStr);
                if(inp < 1 || inp >= currOptionIndex){
                    std::cout << "Input not recognized. Please try again.\n";
                    continue;
                }
                std::cout << purpleboldtext << "-----\n" << resettext;
                break;
            }
            currLocationIndex = regA.getAdj(currLocationIndex)[inp-1];
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
    }
    //std::vector<Enemy> testEnemies;
    //Enemy enemy1 = Enemy("Test Enemy 1", 5, 5, 2, 1, 1, false);
    //Companion companion1 = Companion("Teammate", "Cleric", "Leer");
    //meta.addCompanion(companion1);
    //Enemy enemy2 = Enemy("Test Enemy 2", 10, 5, 4, 1, 1, true);
    //testEnemies.push_back(enemy1);
    //testEnemies.push_back(enemy2);
    //runEncounter(testEnemies, meta, true);
    return 0;
}

//void journalTester(){ // TESTER CODE
//    Journal journal = Journal();
//    journal.addQuest("Test this code.", "You must write tester code to make sure the journal works.", 0, 0);
//    journal.addQuest("Kill Noam.", "You notice your companion Noam is too short. You should find a way to get rid of him.", 2, 1);
//    journal.addQuest("Realize your potential.", "Take over the world!!!", 1, 2);
//    journal.addQuest("Eat ice cream.", "yum.", 1, 100);
//    journal.addQuest("This is an example completed quest.", "uwuwuwuwuwu", 0, 4);
//    if(!journal.advanceQuest(4, -1, "This quest has been completed.", true)) std::cout << "ERROR";
//    journal.addQuest("Pet dog.", "Dog cute must pet.", 3, 3);
//    separatorBar();
//    journal.listQuests(false);
//    separatorBar();
//    journal.listQuests(true);
//    separatorBar();
//}