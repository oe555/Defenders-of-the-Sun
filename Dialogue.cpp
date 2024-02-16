#include "Dialogue.h"
#include <string>
#include <vector>

Dialogue::Dialogue(bool playerChoice_, std::string line_, int perceptionRequirement_, std::string classRequirement_, std::vector<std::string> choices_){
    playerChoice = playerChoice_;
    line = line_;
    perceptionRequirement = perceptionRequirement_;
    classRequirement = classRequirement_;
    choices = choices_;
}

int Dialogue::runDialogue(){
    // TODO: Implement
}