#include "Enemy.h"
#include "Quest.h"
#include "Journal.h"
#include "Weapon.h"
#include "Armor.h"
#include "Companion.h"
#include "Meta.h"
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

void separatorBar(){
    std::cout << "\n#-----#-----#\n\n";
}

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
        std::cout << "\n";
        // actionChoice now stores the name of the action instead of the number from the input
        return inpInt;
    }
    return inpInt;
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

// Return true if they win on their turn
bool enemiesTurn(std::vector<Enemy> &enemies, Meta &meta){
    //separatorBar();
    bool checkCompanions = false;
    for(int currEnemy = 0; currEnemy < (int)enemies.size(); currEnemy++){
        int currTarget = 0;
        if(enemies[currEnemy].isIntelligent()){
            for(int i = 1; i < (int)meta.companions.size(); i++){
                // Find the least health companion that is not down
                if((meta.companions[i].getHealth() < meta.companions[currTarget].getHealth() && meta.companions[i].getHealth() > 0) || meta.companions[currTarget].getHealth() <= 0) currTarget = i;
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
        std::cout << boldtext << "Enemy " << enemies[currEnemy].getName() << " attacks " << meta.companions[currTarget].getName() << ".\n" << resettext;
        if(meta.companions[currTarget].takeDamage(enemies[currEnemy].dealDamage())){
            std::cout << "The enemy's attack was successful.\n";
            std::cout << meta.companions[currTarget].getName() << "'s health has been reduced to " << meta.companions[currTarget].getHealth() << ".\n";
        }
        else{
            std::cout << "The enemy missed their attack.\n";
        }
        if(meta.companions[currTarget].getHealth() <= 0){
            std::cout << redtext << meta.companions[currTarget].getName() << " was knocked unconscious!\n" << resettext;
        }
        separatorBar();
        checkCompanions = true;
        for(int i = 0; i < (int)meta.companions.size(); i++){
            if(meta.companions[i].getHealth() > 0) checkCompanions = false;
        }
        if(checkCompanions) return true;
    }
    for(int i = 0; i < (int)meta.companions.size(); i++){
        if(meta.companions[i].getHealth() > 0) return false;
    }
    return true;
}

// Return true if they win on their turn
bool playerTurn(std::vector<Enemy> &enemies, Meta &meta){
    //separatorBar();
    // TODO: Maybe output some information about the party here
    std::cout << "Your party prepares to attack.\n";
    for(int i = 0; i < (int)meta.companions.size(); i++){
        if(meta.companions[i].getHealth() <= 0){
            std::cout << meta.companions[i].getName() << " is unconscious.\n";
            separatorBar();
            continue;
        }
        else{
            std::cout << meta.companions[i].getName() << "'s current health: " << meta.companions[i].getHealth() << ".\n\n";
        }
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
            std::cout << "\n";
            // actionChoice now stores the name of the action instead of the number from the input
            actionChoice = meta.companions[i].getActions()[actionChoiceInt];
            break;
        }
        /*
            If statements for every possible action
        */
        if(actionChoice == "Attack"){ // Attack----------
            std::cout << "Select the enemy you'd like to attack.\n";
            int targetEnemy = selectEnemy(enemies);
            std::cout << boldtext << meta.companions[i].getName() << " attacks " << enemies[targetEnemy].getName() << "\n" << resettext;
            if(enemies[targetEnemy].takeDamage(meta.companions[i].dealDamage(), meta.companions[i].getWeapon().getPrecisionBonus())){
                std::cout << "Your attack was successful.\n";
                std::cout << enemies[targetEnemy].getName() << "'s health has been reduced to " << enemies[targetEnemy].getHealth() << ".\n";
            }
            else{
                std::cout << "You missed your attack.\n";
            }
            if(enemies[targetEnemy].getHealth() <= 0){
                std::cout << greentext << enemies[targetEnemy].getName() << " was defeated!\n" << resettext;
                enemies.erase(enemies.begin() + targetEnemy);
            }
        }
        if(actionChoice == "Drink Protein"){
            std::cout << "[Dev] Drink Protein was chosen.\n";
        }
        separatorBar();
        if(enemies.empty()){
            return true;
        }
    }
    return false;
}

// Return true if the player loses
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
        return false;
    }
}

int main(){
    //companionTester();
    srand(time(NULL));
    Meta meta = Meta();
    std::vector<Enemy> testEnemies;
    Enemy enemy1 = Enemy("Test Enemy 1", 5, 5, 2, 1, 1, false);
    //Enemy enemy2 = Enemy("Test Enemy 2", 10, 5, 4, 1, 1, true);
    testEnemies.push_back(enemy1);
    //testEnemies.push_back(enemy2);
    runEncounter(testEnemies, meta, true);
    return 0;
}