#include <string>
#include <iostream>
#include <vector>
#include "Meta.h"
#include "Interaction.h"
#include "Rest.h"

bool checkForDigittt(std::string str){ // Checks to see if the user entered some number
    for(int i = 0; i < (int)str.size(); i++){
        if(str[i] >= '0' && str[i] <= '9') return true;
    }
    return false;
}

Rest::Rest(){
    jasperInteraction = Interaction();
    vivianInteraction = Interaction();
    ravenInteraction = Interaction();
    hubertInteraction = Interaction();
    shrugminiInteraction = Interaction();
    irisInteraction = Interaction();
    noamInteraction = Interaction();
}

void Rest::setJasperInteraction(Interaction interaction){
    jasperInteraction = interaction;
}

void Rest::setVivianInteraction(Interaction interaction){
    vivianInteraction = interaction;
}

void Rest::setRavenInteraction(Interaction interaction){
    ravenInteraction = interaction;
}

void Rest::setHubertInteraction(Interaction interaction){
    hubertInteraction = interaction;
}

void Rest::setShrugminiInteraction(Interaction interaction){
    shrugminiInteraction = interaction;
}

void Rest::setIrisInteraction(Interaction interaction){
    irisInteraction = interaction;
}

void Rest::setNoamInteraction(Interaction interaction){
    noamInteraction = interaction;
}

void Rest::executeRest(Meta &meta){
    // JASPER INTERACTION -----
    jasperInteraction.runInteraction(meta);
    // FIRESIDE CHATS -----
    std::cout << "\n#-----#-----#\n\nThe sun goes down and the campfire lights up the nearby area. This is a great opportunity to walk around the campsite and chat with your allies.\n\n#-----#-----#\n\n";
    std::vector<std::string> firesideChatChoices = {};
    for(auto x : meta.companions){
        if(x.getType() == "Vivian" || x.getType() == "Raven" || x.getType() == "Hubert" || x.getType() == "Shrugmini" || x.getType() == "Iris" || x.getType() == "Noam"){
            firesideChatChoices.push_back(x.getType());
        }
    }
    std::string inpString;
    while(!firesideChatChoices.empty()){
        std::cout << "Choose an ally to chat with:\n";
        for(int i = 0; i < (int)firesideChatChoices.size(); i++){
            std::cout << i+1 << ") " << firesideChatChoices[i] << "\n";
        }
        std::string inpString = "";
        int inpInt = 0;
        while(true){
            getline(std::cin, inpString);
            if(!checkForDigittt(inpString)){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
            int inpInt = stoi(inpString);
            inpInt--;
            if(inpInt < 0 || inpInt >= (int)firesideChatChoices.size()){
                std::cout << "Input not recognized. Please try again.\n";
                continue;
            }
        } // inpInt now stores which companion they want to talk to
        inpString = firesideChatChoices[inpInt]; // Get the name of that companion
        firesideChatChoices.erase(firesideChatChoices.begin() + inpInt); // We can't talk to them twice
        // Run the interaction
        if(inpString == "Vivian"){
            vivianInteraction.runInteraction(meta);
        }
        if(inpString == "Raven"){
            ravenInteraction.runInteraction(meta);
        }
        if(inpString == "Hubert"){
            hubertInteraction.runInteraction(meta);
        }
        if(inpString == "Shrugmini"){
            shrugminiInteraction.runInteraction(meta);
        }
        if(inpString == "Iris"){
            irisInteraction.runInteraction(meta);
        }
        if(inpString == "Noam"){
            noamInteraction.runInteraction(meta);
        }
    }
    // ARTISAN -----
    for(auto x : meta.companions){
        if(x.getType() == "Artisan"){ // Artisans can upgrade an armor
            // TODO
        }
    }

    // LEVEL UP -----
    for(int i = 0; i < (int)meta.companions.size(); i++){
        meta.companions[i].levelUp();
    }
    // RESET HP ----- 
    std::cout << "\n#-----#-----#\n\nYour party sleeps well. Everyone has been fully healed.\n\n#-----#-----#\n\n";
    for(int i = 0; i < (int)meta.companions.size(); i++){
        meta.companions[i].setHealth(meta.companions[i].getMaxHealth());
    }
}