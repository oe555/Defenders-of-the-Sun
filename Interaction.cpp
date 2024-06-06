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
    for(int i = 0; i < dialogues_.size(); i++){
        dialogues.push_back(dialogues_[i]);
    }
    interactionNavigator = {};
    questUpdates = {};
    altQuestUpdates = {};
}

void Interaction::addNav(int oldIndex, int returnVal, int newIndex){
    interactionNavigator[{oldIndex, returnVal}] = newIndex;
}

// Return values: 0 - Nothing, 1 - Encounter, 2 - Companion, 3 - Silver, 4 - Weapon, 5 - Armor, 6 - Quest, 7 - Story Update
int Interaction::runInteraction(Meta &meta){
    //std::cout << "[DEBUG] Outputting interaction map:\n";
    //for(auto x : interactionNavigator){
    //    std::cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
    //}
    // TODO - Add special stuff (if statements after running dialogue)
    int currDialogueIndex = 0; // Nonnegative numbers are dialogues, negative numbers are something special
    int dialogueReturnVal = 0;
    std::string trashLine;
    while(true){ // Run dialogues until we get to a resulution
        dialogueReturnVal = dialogues[currDialogueIndex].runDialogue(meta); // Run the first dialogue
        if(!dialogues[currDialogueIndex].isPlayerChoice() && dialogueReturnVal != -1){
            std::cout << "<Press Enter to continue>";
            getline(std::cin, trashLine);
        }
        //std::cout << "[DEBUG] That dialogue (" << currDialogueIndex << ")  returned " << dialogueReturnVal << "\n";
        currDialogueIndex = interactionNavigator[{currDialogueIndex, dialogueReturnVal}]; // Use navigator to go to next thing

        if(currDialogueIndex == -1){ // This resolution ends the dialogue with no special resolution
            return 0; // Nothing
        }
        if(currDialogueIndex == -2){ // This resolutions ends in an encounter
            return 1; // Tell the game to run an ecnounter using the location's enemies
        }
        if(currDialogueIndex == -3){ // This resolution results in the companion joining
            std::cout << "\n#-----#-----#\n\nA new companion has joined your party.\n\n#-----#-----#\n";
            for(auto x : questUpdates){ // We do quest updates here because getting a companion always results in their quest appearing
                if(x.first.first == -1){ // New quest
                    meta.journal.addQuest(x.second.first, x.second.second, x.first.second.second, x.first.second.first);
                }
                else{ // Quest update
                    // Note that we want to complete the quest if the new id is -1 (we no longer care about the id, so -1 is sufficient)
                    meta.journal.advanceQuest(x.first.first, x.first.second.first, x.second.second, (x.first.second.first == -1));
                }
            }
            companion.levelUp();
            meta.addCompanion(companion);
            return 2;
        }
        if(currDialogueIndex == -4){ // This resolution results in gaining a weapon
            std::cout << "\n#-----#-----#\n\nYou gained a new weapon.\n\n#-----#-----#\n";
            meta.addWeapon(weapon);
            return 4;
        }
        if(currDialogueIndex == -5){ // This resolution results in gaining armor
            std::cout << "\n#-----#-----#\n\nYou gained a new piece of armor.\n\n#-----#-----#\n";
            meta.addArmor(armor);
            return 5;
        }
        if(currDialogueIndex == -6){ // This resolution results in gaining silver
            std::cout << "\n#-----#-----#\n\nYou gained " << silver << " silver.\n\n#-----#-----#\n";
            meta.gainSilver(silver);
            return 3;
        }
        if(currDialogueIndex == -7){ // This resolution results in quest updates
            std::cout << "\n#-----#-----#\n\nYour journal has updates.\n\n#-----#-----#\n";
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
        if(currDialogueIndex == -8){ // This resolution updates the story variable
            meta.toggleStoryVariable(storyVariableUpdate);
            std::cout << "\n#-----#-----#\n\nYour journal has updates.\n\n#-----#-----#\n";
            for(auto x : questUpdates){
                if(x.first.first == -1){ // New quest
                    meta.journal.addQuest(x.second.first, x.second.second, x.first.second.second, x.first.second.first);
                }
                else{ // Quest update
                    // Note that we want to complete the quest if the new id is -1 (we no longer care about the id, so -1 is sufficient)
                    meta.journal.advanceQuest(x.first.first, x.first.second.first, x.second.second, (x.first.second.first == -1));
                }
            }
            return 7;
        }
        if(currDialogueIndex == -9){ // Alternate quest updates
            std::cout << "\n#-----#-----#\n\nYour journal has updates.\n\n#-----#-----#\n";
            for(auto x : altQuestUpdates){
                if(x.first.first == -1){ // New quest
                    meta.journal.addQuest(x.second.first, x.second.second, x.first.second.second, x.first.second.first);
                }
                else{ // Quest update
                    // Note that we want to complete the quest if the new id is -1 (we no longer care about the id, so -1 is sufficient)
                    meta.journal.advanceQuest(x.first.first, x.first.second.first, x.second.second, (x.first.second.first == -1));
                }
            }
            return 6;
        }
        if(currDialogueIndex == -10){ // If for whatever reason we want to return something that isn't 0
            return 100;
        }
        // ...
    }
}

// Set oldId to -1 for a new quest, newId to -1 to complete the quest
void Interaction::addQuestUpdate(int oldId, int newId, int type, std::string name, std::string description){
    questUpdates.push_back({{oldId, {newId,type}}, {name, description}});
}

// Set oldId to -1 for a new quest, newId to -1 to complete the quest
void Interaction::addAltQuestUpdate(int oldId, int newId, int type, std::string name, std::string description){
    altQuestUpdates.push_back({{oldId, {newId,type}}, {name, description}});
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

void Interaction::setStoryVariableUpdate(int storyVariableUpdate_){
    storyVariableUpdate = storyVariableUpdate_;
}