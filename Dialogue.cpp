#include "Dialogue.h"
#include "Meta.h"
#include <string>
#include <vector>
#include <iostream>

Dialogue::Dialogue(bool playerChoice_, std::string line_, int perceptionRequirement_, int charismaRequirement_, std::string classRequirement_, std::vector<std::string> choices_){
    playerChoice = playerChoice_;
    line = line_;
    perceptionRequirement = perceptionRequirement_;
    charismaRequirement = charismaRequirement_;
    classRequirement = classRequirement_;
    choices = choices_;
}

int Dialogue::runDialogue(Meta meta){
    if((rand() % 10) + 1 + meta.getPerception() < perceptionRequirement){ // You must hit a perception check to see a dialogue
        return -1; // Returns -1 on a failed perception check
    }
    if(classRequirement != "None"){
        for(Companion x : meta.companions){
            if(x.getName() == meta.getCharName()){
                if(classRequirement != x.getType()){
                    return -1; // Not the correct class to see this dialogue
                }
            }
        }
    }
    std::cout << "\n#-----#-----#\n\n";
    std::cout << line << "\n";
    if(!playerChoice){
        // TODO
    }
    else{ // This is what to do if it's a player choice.
        // TODO
    }

}