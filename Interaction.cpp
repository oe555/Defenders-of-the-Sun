#include <string>
#include <vector>
#include <map>
#include "Dialogue.h"
#include "Interaction.h"

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