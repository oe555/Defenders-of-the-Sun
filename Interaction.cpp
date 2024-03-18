#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Dialogue.h"
#include "Interaction.h"

Interaction::Interaction(){
    dialogues = {};
}

Interaction::Interaction(std::vector<Dialogue> dialogues_){
    dialogues = dialogues_;
    interactionNavigator = {};
    questUpdates = {};
}

void Interaction::addNav(int oldIndex, int returnVal, int newIndex){
    interactionNavigator[{oldIndex, returnVal}] = newIndex;
}

// Return values: 0 - Nothing, 1 - Encounter, 2 - Companion, 3 - Silver, 4 - Weapon, 5 - Armor, 6 - Quest
int Interaction::runInteraction(Meta &meta){
    // TODO - Add special stuff (if statements after running dialogue)
    int currDialogueIndex = 0; // Nonnegative numbers are dialogues, negative numbers are something special
    int dialogueReturnVal = 0;
    while(true){ // Run dialogues until we get to a resulution
        dialogueReturnVal = dialogues[currDialogueIndex].runDialogue(meta); // Run the first dialogue
        currDialogueIndex = interactionNavigator[{currDialogueIndex, dialogueReturnVal}]; // Use navigator to go to next thing
        if(currDialogueIndex == -1){ // This resolution ends the dialogue with no special resolution
            return 0; // Nothing
        }
        if(currDialogueIndex == -2){ // This resolutions ends in an encounter
            return 1; // Tell the game to run an ecnounter using the location's enemies
        }
        if(currDialogueIndex == -3){ // This resolution results in the companion joining
            std::cout << "\n#-----#-----#\n\nA new companion has joined your party.\n\n#-----#-----#\n";
            meta.addCompanion(companion);
            return 2;
        }
        if(currDialogueIndex == -4){ // This resolution results in gaining a weapon
            meta.addWeapon(weapon);
            return 4;
        }
        if(currDialogueIndex == -5){ // This resolution results in gaining armor
            meta.addArmor(armor);
            return 5;
        }
        if(currDialogueIndex == -6){ // This resolution results in gaining silver
            meta.gainSilver(silver);
            return 3;
        }
        if(currDialogueIndex == -7){ // This resolution results in quest updates
            for(auto x : questUpdates){
                if(x.first.first == -1){ // New quest
                    meta.journal.addQuest(x.second.first, x.second.second, x.first.second.second, x.first.second.first);
                }
                else{ // Quest update
                    // Note that we want to complete the quest if the new id is -1 (we no longer care about the id, so -1 is sufficient)
                    meta.journal.advanceQuest(x.first.first, x.first.second.first, x.second.second, (x.first.second.first == -1));
                }
            }
            return 6; // Tells the main function to indicate to the player that the journal was updated
        }
        // ...
    }
}

void Interaction::addQuestUpdate(int oldId, int newId, int type, std::string name, std::string description){
    questUpdates.push_back({{oldId, {newId,type}}, {name, description}});
}

void Interaction::addCompanion(std::string name, std::string deity){
    companion = Companion(name, name, deity);
}

void Interaction::addArmor(Armor armor_){
    armor = armor_;
}

void Interaction::addWeapon(Weapon weapon_){
    weapon = weapon_;
}

void Interaction::setSilver(int silver_){
    silver = silver_;
}