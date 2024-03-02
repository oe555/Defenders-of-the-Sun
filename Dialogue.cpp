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
    if(!playerChoice){ // Not a player choice
        // Check class requirement
        if(classRequirement != "None"){
            for(Companion x : meta.companions){
                if(x.getName() == meta.getCharName()){
                    if(classRequirement != x.getType()){
                        return -1; // Not the correct class to see this dialogue
                    }
                }
            }
        }
        // Check perception
        if((rand() % 10) + 1 + meta.getPerception() < perceptionRequirement){ // You must hit a perception check to see a dialogue
            return -1; // Returns -1 on a failed perception check
        }
        std::cout << "\n#-----#-----#\n\n";
        std::cout << line << "\n";
        return 0; // Successfully showed the line
    }
    else{ // This is what to do if it's a player choice.
        std::cout << "\n#-----#-----#\n\n";
        std::cout << line << "\n";
        bool perceptionFailed = false;
        if((rand() % 10) + 1 + meta.getPerception() < perceptionRequirement){
            perceptionFailed = true; // The perception check was failed... Don't show first choice.
        }
        int currChoice = 1;
        bool firstChoiceShown = true; // This will tell us whether we need to change the number we return
        for(int i = 0; i < choices.size(); i++){ // Output choices
            if(i == 0){ // The first choice is usually special
                if(perceptionFailed){ // Don't show the first choice if the perception is failed.
                    firstChoiceShown = false;
                    continue;
                }  
                if(classRequirement != "None"){ // This checks to see if the main character is a different class than required
                    for(Companion x : meta.companions){
                        if(x.getName() == meta.getCharName()){
                            if(classRequirement != x.getType()){
                                firstChoiceShown = false;
                                continue; // Not the correct class to see this choice
                            }
                        }
                    }
                }
            }
            std::cout << currChoice << ") " << choices[i] << "\n.";
            currChoice++;
        } // Done outputting choices
        // The user will now enter which choice they want to make
        std::string inpString = "";
        int inpInt = 0;
        while(true){
            getline(std::cin, inpString);
            // TODO: Potential runtime error
            int inpInt = stoi(inpString);
            if(inpInt <= 0 || inpInt >= currChoice) { // Make sure the input is one of the choices
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            std::cout << "\033[1;35m" << "-----\n" << "\033[0;0m"; // Purple bold line
        }
        if(!firstChoiceShown) inpInt++; // The player did not actually pick the right number if the first choice wasn't there
        return inpInt;
    }
}