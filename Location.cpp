#include "Location.h"
#include <string>

Location::Location(std::string name_){
    name = name_;
    hasPrimaryInteraction = false;
    hasPostEncounterInteraction = false;
    encounter = {};
    optionalInteractions = {};
    numOptionalInteractions = 0;
    // Interaction has a default constructor
}

std::string Location::getName(){
    return name;
}

bool Location::getHasPrimaryInteraction(){
    return hasPrimaryInteraction;
}

bool Location::getHasPostEncounterInteraction(){
    return hasPostEncounterInteraction;
}

Interaction Location::getPrimaryInteraction(){
    hasPrimaryInteraction = false;
    return primaryInteraction;
}

void Location::setPrimaryInteraction(Interaction interaction_){
    hasPrimaryInteraction = true;
    primaryInteraction = interaction_;
}

Interaction Location::getPostEncounterInteraction(){
    hasPostEncounterInteraction = false;
    return postEncounterInteraction;
}

void Location::setPostEncounterInteraction(Interaction interaction_){
    hasPostEncounterInteraction = true;
    postEncounterInteraction = interaction_;
}

std::vector<Enemy> Location::getEnemies(){
    return encounter;
}

void Location::addEnemy(Enemy enemy_){
    encounter.push_back(enemy_);
}

int Location::getNumOptionalInteractions(){
    return numOptionalInteractions;
}

std::pair<std::string, Interaction> Location::getOptionalInteraction(int index_){
    std::pair<std::string, Interaction> temp = optionalInteractions[index_];
    optionalInteractions.erase(optionalInteractions.begin() + index_);
    numOptionalInteractions--;
    return temp;
}

void Location::addOptionalInteraction(std::pair<std::string, Interaction> interaction_){
    numOptionalInteractions++;
    optionalInteractions.push_back(interaction_);
}


