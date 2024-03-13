#include <string>
#include <vector>
#include <map>
#include "Dialogue.h"
#include "Interaction.h"

Interaction::Interaction(std::vector<Dialogue> dialogues_){
    dialogues = dialogues_;
    interactionNavigator = {};
}

void Interaction::addNav(int oldIndex, int returnVal, int newIndex){
    interactionNavigator[{oldIndex, returnVal}] = newIndex;
}

// Return values: 0 - Nothing, 1 - Encounter, 2 - Companion, 3 - Silver, 4 - Weapon, 5 - Armor, 6 - Quest
int Interaction::runInteraction(Meta meta){
    // TODO - Add special stuff (if statements after running dialogue)
    int currDialogueIndex = 0; // Nonnegative numbers are dialogues, negative numbers are something special
    int dialogueReturnVal = 0;
    while(true){ // Run dialogues until we get to a resulution
        dialogueReturnVal = dialogues[currDialogueIndex].runDialogue(meta); // Run the first dialogue
        currDialogueIndex = interactionNavigator[{currDialogueIndex, dialogueReturnVal}]; // Use navigator to go to next thing
        if(currDialogueIndex == -1){ // This resolution ends the dialogue with no special resolution
            return 0; // Nothing
        }
        // ...
    }
}