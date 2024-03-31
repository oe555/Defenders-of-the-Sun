#include "Dialogue.h"
#include "Meta.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

bool checkForDigit2(std::string str){ // Checks to see if the user entered some number
    for(int i = 0; i < (int)str.size(); i++){
        if(str[i] >= '0' && str[i] <= '9') return true;
    }
    return false;
}

// TODO: This is the same as pad in Game.cpp, but giving it the same name causes a compiletime error
std::string pad2(std::string str){
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

Dialogue::Dialogue(std::string line_){
    playerChoice = false;
    line = line_;
    storyVariableRequirement = -1;
    perceptionRequirement = -99;
    charismaRequirement = -99;
    classRequirement = "None";
    companionRequirement = "None";
    deityRequirement = "None";
    choices = {};
}

Dialogue::Dialogue(std::string line_, std::vector<std::string> choices_){
    playerChoice = true;
    line = line_;
    storyVariableRequirement = -1;
    perceptionRequirement = -99;
    charismaRequirement = -99;
    classRequirement = "None";
    companionRequirement = "None";
    deityRequirement = "None";
    choices = choices_;
}

Dialogue::Dialogue(bool playerChoice_, std::string line_, int storyVariableRequirement_, int perceptionRequirement_, int charismaRequirement_, std::string classRequirement_, std::string companionRequirement_, std::string deityRequirement_, std::vector<std::string> choices_){
    playerChoice = playerChoice_;
    line = line_;
    storyVariableRequirement = storyVariableRequirement_;
    perceptionRequirement = perceptionRequirement_;
    charismaRequirement = charismaRequirement_;
    classRequirement = classRequirement_;
    companionRequirement = companionRequirement_;
    deityRequirement = deityRequirement_;
    choices = choices_;
}

// If it's a player choice, then this will return the index of what the player chooses. Returns -1 on any fail. Returns 0 otherwise.
int Dialogue::runDialogue(Meta meta){
    if(!playerChoice){ // Not a player choice
        // Check class requirement
        if(storyVariableRequirement != -1){
            if(!meta.getStoryVariable(storyVariableRequirement)){
                return -1; // The story variable is not true, so we fail here
            }
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
        // Check companion requirement
        if(companionRequirement != "None"){
            bool ok = false;
            for(Companion x : meta.companions){
                if(x.getName() == companionRequirement){
                    ok = true; // We found the companion
                }
            }
            if(!ok) return -1; // Companion not found
        }
        // Check deity requirement
        if(deityRequirement != "None"){
            if(meta.getCharDeity() != deityRequirement){
                return -1; // Not the correct worship
            }
        }
        // Check perception
        if((rand() % 10) + 1 + meta.getPerception() < perceptionRequirement){ // You must hit a perception check to see a dialogue
            return -1; // Returns -1 on a failed perception check
        }
        std::cout << "\n#-----#-----#\n\n";
        std::cout << pad2(line) << "\n";
        return 0; // Successfully showed the line
    }
    else{ // This is what to do if it's a player choice.
        std::cout << "\n#-----#-----#\n\n";
        std::cout << pad2(line) << "\n";
        bool perceptionFailed = false;
        if((rand() % 10) + 1 + meta.getPerception() < perceptionRequirement){
            perceptionFailed = true; // The perception check was failed... Don't show first choice.
        }
        int currChoice = 1;
        bool firstChoiceShown = true; // This will tell us whether we need to change the number we return
        for(int i = 0; i < choices.size(); i++){ // Output choices
            if(i == 0){ // The first choice is usually special, let's decide if they see it
                if(storyVariableRequirement != -1){
                    if(!meta.getStoryVariable(storyVariableRequirement)){ // Don't show the first choice bc the story variable isn't true
                        firstChoiceShown = false;
                        continue;
                    }
                }
                if(perceptionFailed){ // Don't show the first choice if the perception is failed
                    firstChoiceShown = false;
                    continue;
                }  
                if(classRequirement != "None"){ // This checks to see if the main character is a different class than required
                    for(Companion x : meta.companions){
                        if(x.getName() == meta.getCharName()){
                            if(classRequirement != x.getType()){
                                firstChoiceShown = false;
                                break; 
                            }
                        }
                    }
                    if(!firstChoiceShown) continue; // Not the correct class to see this choice
                }
                if(companionRequirement != "None"){
                    bool ok = false;
                    for(Companion x : meta.companions){
                        if(x.getName() == companionRequirement){
                            ok = true; // We found the companion
                        }
                    }
                    if(!ok){
                        firstChoiceShown = false;
                        continue; // Companion not found, can't see this choice
                    }
                }
                if(deityRequirement != "None"){ // Must check deity
                    if(meta.getCharDeity() != deityRequirement){
                        firstChoiceShown = false;
                        continue;
                    }
                }
            }
            std::cout << currChoice << ") " << choices[i] << "\n";
            currChoice++;
        } // Done outputting choices
        // The user will now enter which choice they want to make
        std::string inpString = "";
        int inpInt = 0;
        while(true){
            getline(std::cin, inpString);
            if(!checkForDigit2(inpString)){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            inpInt = stoi(inpString);
            if(inpInt <= 0 || inpInt >= currChoice) { // Make sure the input is one of the choices (currChoice is 1 more than the number of choices)
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            std::cout << "\033[1;35m" << "-----\n" << "\033[0;0m"; // Purple bold line
            break;
        }

        if(!firstChoiceShown) inpInt++; // The player did not actually pick the right number if the first choice wasn't there

        //Must make charisma check if they picked first option
        if(inpInt == 1){
            if((rand() % 10) + 1 + meta.getCharisma() < charismaRequirement){
                return -1; // The rizz check failed
            }
        }
        
        // Approval
        for(auto x : approval){
            if(inpInt == x.second){ // This approval is related to this choice
                for(int i = 0; i < (int)meta.companions.size(); i++){
                    if(meta.companions[i].getName() == x.first.first){
                        meta.companions[i].adjustApproval(x.first.second);
                        if(x.first.second == -3) std::cout << "\n\033[1;31m" << x.first.first << " strongly dissaproves.\n\033[0;0m";
                        if(x.first.second == -2) std::cout << "\n\033[0;31m" << x.first.first << " dissaproves.\n\033[0;0m";
                        if(x.first.second == -1) std::cout << "\n\033[0;31m" << x.first.first << " slightly dissaproves.\n\033[0;0m";
                        if(x.first.second == 2) std::cout << "\n\033[0;32m" << x.first.first << " approves.\n\033[0;0m";
                        if(x.first.second == 3) std::cout << "\n\033[1;32m" << x.first.first << " strongly approves.\n\033[0;0m";
                    }
                }
            }
        }
        //std::cout << "DEBUG\n";
        return inpInt; // Return what the player picked
    }
}

bool Dialogue::isPlayerChoice(){
    return playerChoice;
}

void Dialogue::addApproval(std::string companion, int value, int index){
    approval.push_back({{companion, value}, index});
}